#include <linux/random.h>
#include <ncurses.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "emulate.h"

#include "alienos.h"
#include "colors.h"
#include "common.h"
#include "error.h"

#if !defined(SYS_getrandom) && defined(__x86_64__)
#define SYS_getrandom 318
#endif

void emulate_end(int status) {
  if (EXIT_CODE_MIN <= status && status <= EXIT_CODE_MAX) {
    exit(status);
  } else {
    err_unknown_exit_code(status);
  }
}

uint32_t emulate_getrand() {
  uint32_t rand_val;
  CALL_NEQ(-1, syscall(SYS_getrandom, &rand_val, sizeof(rand_val), 0));
  return rand_val;
}

int emulate_getkey() {
  int nchar = getch();
  switch (nchar) {
    case KEY_UP:
      return ALIEN_KEY_UP;
    case KEY_DOWN:
      return ALIEN_KEY_DOWN;
    case KEY_LEFT:
      return ALIEN_KEY_LEFT;
    case KEY_RIGHT:
      return ALIEN_KEY_RIGHT;
    case KEY_ENTER:
    case ALIEN_KEY_ENTER:
      return ALIEN_KEY_ENTER;
    default:
      if (ALIEN_ASCII_LOWEST_KEY <= nchar && nchar <= ALIEN_ASCII_HIGHEST_KEY) {
        return nchar;
      } else {
        err_unknown_key(nchar);
      }
  }
}

void check_terminal_area_access(int y, int x) {
  if (y < 0 || y >= WIN_HEIGHT || x < 0 || x >= WIN_WIDTH) {
    SIMPLE_ERR("Alien process tried to print outside terminal window.");
  }
}

void check_char_value(char c) {
  if (c < MIN_PRINTABLE_CHAR_ASCII_VAL || MAX_PRINTABLE_CHAR_ASCII_VAL < c) {
    SIMPLE_ERR("Alien process tried to print invalid character.");
  }
}

void emulate_print(int y, int x, uint16_t *chars, int n) {
  int orig_y;
  int orig_x;
  getsyx(orig_y, orig_x);
  for (int i = 0; i < n; i++) {
    check_char_value((char)(chars[i] & CHAR_MASK));
    check_terminal_area_access(y, x + i);
    set_pair_w_color_on_black(DEFAULT_PAIR, get_letter_color(chars[i]));
    CALL_NEQ(ERR, attron(COLOR_PAIR(DEFAULT_PAIR)));
    CALL_NEQ(ERR, mvdelch(y, x + i));
    CALL_NEQ(ERR, mvinsch(y, x + i, chars[i] & CHAR_MASK));
    CALL_NEQ(ERR, attroff(COLOR_PAIR(DEFAULT_PAIR)));
  }
  CALL_NEQ(ERR, wnoutrefresh(stdscr));
  setsyx(orig_y, orig_x);
  CALL_NEQ(ERR, doupdate());
}

void emulate_setcursor(int y, int x) {
  check_terminal_area_access(y, x);
  CALL_NEQ(ERR, move(y, x));
  CALL_NEQ(ERR, refresh());
}