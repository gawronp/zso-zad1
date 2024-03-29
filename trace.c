#include <sys/ptrace.h>
#include <asm/ptrace.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>

#include "trace.h"

#include "common.h"
#include "emulate.h"
#include "error.h"

void wait_and_exit_if_alien_exited() {
  int status;
  wait(&status);
  if (WIFEXITED(status) || WIFSIGNALED(status)) {
    SIMPLE_ERR("Alien process exited unexpectedly.");
  }
}

void process_getkey(pid_t pid) {
  int c = emulate_getkey();
  set_return_value_reg(pid, (uint64_t)c);
}

void process_getrand(pid_t pid) {
  uint32_t r = emulate_getrand();
  set_return_value_reg(pid, (uint64_t)r);
}

void process_print(pid_t pid, struct user_regs_struct *regs) {
  uint16_t *local_copy = malloc(sizeof(uint16_t) * regs->r10);
  if (local_copy == NULL) {
    CALL_ERR("Malloc failed.");
  }
  copy_to_host(pid, (void *)local_copy, (void *)regs->rdx,
               sizeof(uint16_t) * regs->r10);
  emulate_print(regs->rsi, regs->rdi, local_copy, regs->r10);
  free(local_copy);
}

void execute(char *const path, struct section_info params_section,
             const int *params_vals) {
  pid_t sandbox_pid = fork();
  CALL_NEQ(-1, sandbox_pid);
  if (sandbox_pid == 0) {
    CALL_NEQ_ERRNO(-1, ptrace(PTRACE_TRACEME, 0, NULL, NULL));
    CALL_NEQ_ERRNO(-1, prctl(PR_SET_PDEATHSIG, SIGKILL, 0, 0, 0));
    char *const args[] = {path, NULL};
    execve(path, args, NULL);
  } else {
    wait_and_exit_if_alien_exited();
    // execve done, we set program parameters:
    if (params_section.length_bytes > 0) {
      copy_to_guest(sandbox_pid, (void *)params_vals,
                    (void *)params_section.memory_addr,
                    params_section.length_bytes);
    }
    while (1) {
      CALL_NEQ_ERRNO(-1, ptrace(PTRACE_SYSEMU, sandbox_pid, NULL, NULL));
      wait_and_exit_if_alien_exited();
      struct user_regs_struct regs = get_registers(sandbox_pid);
      switch (regs.orig_rax) {
        case SYSCALL_END:
          emulate_end(regs.rdi);
          break;
        case SYSCALL_GETRAND:
          process_getrand(sandbox_pid);
          break;
        case SYSCALL_GETKEY:
          process_getkey(sandbox_pid);
          break;
        case SYSCALL_PRINT:
          process_print(sandbox_pid, &regs);
          break;
        case SYSCALL_SETCURSOR:
          emulate_setcursor(regs.rsi, regs.rdi);
          break;
        default:
          err_invalid_syscall_num(regs.orig_rax);
          break;
      }
    }
  }
}
