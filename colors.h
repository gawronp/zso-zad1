#ifndef _COLORS_H_
#define _COLORS_H_

#include <ncurses.h>

#define A_BLACK         0b0000
#define A_BLUE          0b0001
#define A_GREEN         0b0010
#define A_TURQOISE      0b0011
#define A_RED           0b0100
#define A_PINK          0b0101
#define A_YELLOW        0b0110
#define A_L_GREY        0b0111
#define A_D_GREY        0b1000
#define A_L_BLUE        0b1001
#define A_L_GREEN       0b1010
#define A_L_TURQOISE    0b1011
#define A_L_RED         0b1100
#define A_L_PINK        0b1101
#define A_L_YELLOW      0b1110
#define A_WHITE         0b1111

#define COLOR_MASK      0b0000111100000000

#define DEFAULT_COLOR_FOR_FOREGROUND 1
#define DEFAULT_PAIR 1

int init_color_to(int color_id, int color_code) {
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

int get_letter_color(uint16_t letter) {
    return letter & COLOR_MASK;
}

void set_pair_w_color_on_black(int pair_id, int color_code) {
    init_color_to(DEFAULT_COLOR_FOR_FOREGROUND, color_code);
    init_pair(pair_id, DEFAULT_COLOR_FOR_FOREGROUND, COLOR_BLACK);
}

#endif