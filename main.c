#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#include "trace.h"
#include "error.h"
#include "elf.h"

int main(int argc, char **argv) {
    int provided_args_for_alien_prog = argc - 2;
    int *params = malloc(provided_args_for_alien_prog * sizeof(int));
    for (int i = 2; i < argc; i++) {
        int len = strlen(argv[i]);
        for (int pos = 0; pos < len; pos++) {
            if (!isdigit(argv[i][pos])) {
                err_simple_message("Arguments given for alien program are not numbers!");
            }
        }
        params[i - 2] = atoi(argv[i]);
    }

    struct section_info params_section = get_params_section_info(argv[1]);
    if (params_section.length_bytes / sizeof(int) != provided_args_for_alien_prog) {
        err_simple_message("Provided different arguments count from arguments count of alien program.");
    }

    initscr();
    atexit((void (*)(void)) endwin);
    keypad(stdscr, true);
    resizeterm(24, 80);
    refresh();
    execute(argv[1], params_section, params);
}