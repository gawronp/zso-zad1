#define _GNU_SOURCE

#include <stdlib.h>
#include <sys/uio.h>
#include <sys/user.h>
#include <sys/ptrace.h>

void copy_to_host(pid_t pid, void *start_local, void *start_remote, int length) {
    struct iovec local = {
            .iov_base = start_local,
            .iov_len = length
    };
    struct iovec remote = {
            .iov_base = start_remote,
            .iov_len = length
    };
    process_vm_readv(pid, &local, 1, &remote, 1, 0);
}

void copy_to_guest(pid_t pid, void *start_local, void *start_remote, int length) {
    struct iovec local = {
            .iov_base = start_local,
            .iov_len = length
    };
    struct iovec remote = {
            .iov_base = start_remote,
            .iov_len = length
    };
    process_vm_writev(pid, &local, 1, &remote, 1, 0);
}

struct user_regs_struct get_registers(pid_t pid) {
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, NULL, &regs);
    return regs;
}

void set_return_value_reg(pid_t pid, unsigned long long int val) {
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, NULL, &regs);
    regs.rax = val;
    ptrace(PTRACE_SETREGS, pid, NULL, &regs);
}