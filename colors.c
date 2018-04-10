#include <ncurses.h>

#include "colors.h"
#include "error.h"

void init_color_pairs() {
  if (COLOR_PAIRS < 8) {
    SIMPLE_ERR("Not enough color pairs available.");
  }

  CALL_NEQ(ERR, init_pair(A_BLACK + 1, COLOR_BLACK, COLOR_BLACK));
  CALL_NEQ(ERR, init_pair(A_BLUE + 1, COLOR_BLUE, COLOR_BLACK));
  CALL_NEQ(ERR, init_pair(A_GREEN + 1, COLOR_GREEN, COLOR_BLACK));
  CALL_NEQ(ERR, init_pair(A_TURQOISE + 1, COLOR_CYAN, COLOR_BLACK));
  CALL_NEQ(ERR, init_pair(A_RED + 1, COLOR_RED, COLOR_BLACK));
  CALL_NEQ(ERR, init_pair(A_PINK + 1, COLOR_MAGENTA, COLOR_BLACK));
  CALL_NEQ(ERR, init_pair(A_YELLOW + 1, COLOR_YELLOW, COLOR_BLACK));
  CALL_NEQ(ERR, init_pair(A_WHITE + 1, COLOR_WHITE, COLOR_BLACK));
}

int get_color_attr(int color_code) {
  color_code++;
  switch (color_code) {
    case A_BLACK:
      return COLOR_PAIR(A_BLACK);
    case A_BLUE:
      return COLOR_PAIR(A_BLUE);
    case A_GREEN:
      return COLOR_PAIR(A_GREEN);
    case A_TURQOISE:
      return COLOR_PAIR(A_TURQOISE);
    case A_RED:
      return COLOR_PAIR(A_RED);
    case A_PINK:
      return COLOR_PAIR(A_PINK);
    case A_YELLOW:
      return COLOR_PAIR(A_YELLOW);
    case A_L_GREY:
      return COLOR_PAIR(A_BLACK) | A_BOLD;
    case A_D_GREY:
      return COLOR_PAIR(A_BLACK) | A_DIM;
    case A_L_BLUE:
      return COLOR_PAIR(A_BLUE) | A_BOLD;
    case A_L_GREEN:
      return COLOR_PAIR(A_GREEN) | A_BOLD;
    case A_L_TURQOISE:
      return COLOR_PAIR(A_TURQOISE) | A_BOLD;
    case A_L_RED:
      return COLOR_PAIR(A_RED) | A_BOLD;
    case A_L_PINK:
      return COLOR_PAIR(A_PINK) | A_BOLD;
    case A_L_YELLOW:
      return COLOR_PAIR(A_YELLOW) | A_BOLD;
    case A_WHITE:
      return COLOR_PAIR(A_WHITE);
  }
  SIMPLE_ERR("Unknown color requested.");
}

int get_letter_color(uint16_t letter) { return (letter & COLOR_MASK) >> 8; }