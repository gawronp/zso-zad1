#include <stdio.h>
#include <stdlib.h>

#include "error.h"

noreturn void err_invalid_syscall_num(const int syscall_id) {
  errx(ERROR_EMU, "No such syscall: %d\n", syscall_id);
}

noreturn void err_unknown_key(const int key_ncurses_val) {
  errx(ERROR_EMU, "Unknown key, ncurses code: %d\n", key_ncurses_val);
}

noreturn void err_unknown_exit_code(const int exit_code) {
  errx(ERROR_EMU, "Unknown exit code: %d\n", exit_code);
}