#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdnoreturn.h>

#define ERROR_EMU 127

noreturn void err_simple_message(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(ERROR_EMU);
}

noreturn void err_invalid_syscall_num(const int syscall_id) {
    fprintf(stderr, "No such syscall: %d !!!\n", syscall_id);
    exit(ERROR_EMU);
}

noreturn void err_unknown_key(const int key_ncurses_val) {
    fprintf(stderr, "Unknown key, ncurses code: %d\n", key_ncurses_val);
    exit(ERROR_EMU);
}

void err_execution_failure_conditional(bool is_failure, const char *error_message) {
    if (is_failure) {
        fprintf(stderr, "%s\n", error_message);
        exit(ERROR_EMU);
    }
}

#endif