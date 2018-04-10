#include <ctype.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alienos.h"
#include "elf.h"
#include "error.h"
#include "trace.h"

int main(int argc, char **argv) {
  if (argc <= 1) {
    SIMPLE_ERR(
        "Too few arguments, at least one argument required (path to alien "
        "program).");
  }

  unsigned int provided_args_for_alien_prog = (unsigned int)argc - 2;
  int *params = malloc(provided_args_for_alien_prog * sizeof(int));
  for (int i = 2; i < argc; i++) {
    int len = strlen(argv[i]);
    for (int pos = 0; pos < len; pos++) {
      if (!isdigit(argv[i][pos])) {
        SIMPLE_ERR("Arguments given for alien program are not numbers!");
      }
    }
    params[i - 2] = atoi(argv[i]);
  }

  struct section_info params_section = get_params_section_info(argv[1]);
  if (params_section.length_bytes / sizeof(int) !=
      provided_args_for_alien_prog) {
    SIMPLE_ERR(
        "Provided different arguments count from arguments count of alien "
        "program.");
  }

  initscr();
  noecho();
  atexit((void (*)(void))endwin);
  keypad(stdscr, true);
  resizeterm(WIN_HEIGHT, WIN_WIDTH);
  (void)getch();  // we don't need to read KEY_RESIZE later
  refresh();
  execute(argv[1], params_section, params);
}