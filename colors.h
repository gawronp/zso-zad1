#ifndef _COLORS_H_
#define _COLORS_H_

#define A_BLACK         0x0
#define A_BLUE          0x1
#define A_GREEN         0x2
#define A_TURQOISE      0x3
#define A_RED           0x4
#define A_PINK          0x5
#define A_YELLOW        0x6
#define A_L_GREY        0x7
#define A_D_GREY        0x8
#define A_L_BLUE        0x9
#define A_L_GREEN       0xa
#define A_L_TURQOISE    0xb
#define A_L_RED         0xc
#define A_L_PINK        0xd
#define A_L_YELLOW      0xe
#define A_WHITE         0xf

#define COLOR_MASK      0x0f00

#define DEFAULT_COLOR_FOR_FOREGROUND 1
#define DEFAULT_PAIR 1

int get_letter_color(uint16_t letter);

void set_pair_w_color_on_black(int pair_id, int color_code);

#endif