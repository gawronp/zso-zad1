#include <ncurses.h>

#include "colors.h"

void init_color_to(int color_id, int color_code) {
  switch (color_code) {
    case A_BLACK:
      init_color(color_id, 0, 0, 0);
      break;
    case A_BLUE:
      init_color(color_id, 0, 0, 1000);
      break;
    case A_GREEN:
      init_color(color_id, 0, 1000, 0);
      break;
    case A_TURQOISE:
      init_color(color_id, 0, 1000, 1000);
      break;
    case A_RED:
      init_color(color_id, 1000, 0, 0);
      break;
    case A_PINK:
      init_color(color_id, 1000, 0, 1000);
      break;
    case A_YELLOW:
      init_color(color_id, 1000, 1000, 0);
      break;
    case A_L_GREY:
      init_color(color_id, 700, 700, 700);
      break;
    case A_D_GREY:
      init_color(color_id, 400, 400, 400);
      break;
    case A_L_BLUE:
      init_color(color_id, 600, 800, 1000);
      break;
    case A_L_GREEN:
      init_color(color_id, 800, 1000, 600);
      break;
    case A_L_TURQOISE:
      init_color(color_id, 600, 1000, 1000);
      break;
    case A_L_RED:
      init_color(color_id, 1000, 600, 600);
      break;
    case A_L_PINK:
      init_color(color_id, 1000, 600, 1000);
      break;
    case A_L_YELLOW:
      init_color(color_id, 1000, 1000, 600);
      break;
    case A_WHITE:
      init_color(color_id, 1000, 1000, 1000);
      break;
  }
}

int get_letter_color(uint16_t letter) { return letter & COLOR_MASK; }

void set_pair_w_color_on_black(int pair_id, int color_code) {
  init_color_to(DEFAULT_COLOR_FOR_FOREGROUND, color_code);
  init_pair(pair_id, DEFAULT_COLOR_FOR_FOREGROUND, COLOR_BLACK);
}