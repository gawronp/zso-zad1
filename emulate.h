#include <stdlib.h>
#include <sys/syscall.h>
#include <linux/random.h>
#include <ncurses.h>
#include <unistd.h>

#if !defined(SYS_getrandom) && defined(__x86_64__)
#define SYS_getrandom 318
#endif

#include "alienos.h"
#include "common.h"
#include "colors.h"
#include "error.h"

#define SYSCALL_END 0
#define SYSCALL_GETRAND 1
#define SYSCALL_GETKEY 2
#define SYSCALL_PRINT 3
#define SYSCALL_SETCURSOR 4

#define CHAR_MASK 0b0000000011111111

#define WIN_WIDTH 80
#define WIN_HEIGHT 24

void emulate_end(int status) {
    exit(status);
}

uint32_t emulate_getrand() {
    uint32_t rand_val;
    err_execution_failure_conditional(0 == syscall(SYS_getrandom, &rand_val, sizeof(rand_val), 0),
                                      "Failed getting random value through syscall");
    return rand_val;
}

char emulate_getkey() {
    int nchar = getch();
    char c;
    switch (nchar) {
        case KEY_UP:
            c = ALIEN_KEY_UP;
            break;
        case KEY_DOWN:
            c = ALIEN_KEY_DOWN;
            break;
        case KEY_LEFT:
            c = ALIEN_KEY_LEFT;
            break;
        case KEY_RIGHT:
            c = ALIEN_KEY_RIGHT;
            break;
        case KEY_ENTER:
            c = ALIEN_KEY_ENTER;
            break;
        default:
            if (ALIEN_ASCII_LOWEST_KEY <= nchar && nchar <= ALIEN_ASCII_HIGHEST_KEY) {
                c = (char) nchar;
            } else {
                err_unknown_key(nchar);
            }
    }
    return c;
}

void check_terminal_area_access(int y, int x) {
    if (y < 0 || y > WIN_HEIGHT || x < 0 || x > WIN_WIDTH) {
        err_simple_message( "Alien process tried to print outside terminal window.");
    }
}

void emulate_print(int y, int x, uint16_t *chars, int n) {
    int orig_y;
    int orig_x;
    getsyx(orig_y, orig_x);
    for (int i = 0; i < n; i++) {
        check_terminal_area_access(orig_y, orig_x + i);
        set_pair_w_color_on_black(DEFAULT_PAIR, get_letter_color(chars[i]));
        err_execution_failure_conditional(ERR == attron(COLOR_PAIR(DEFAULT_PAIR)),
                                          "Error setting color pair in ncurses.");
        err_execution_failure_conditional(ERR == mvaddch(y, x + i, chars[i] & CHAR_MASK),
                                          "Error adding char to ncurses window.");
        err_execution_failure_conditional(ERR == attroff(COLOR_PAIR(DEFAULT_PAIR)),
                                          "Error disabling previous color pair in ncurses.");
    }
    setsyx(orig_y, orig_x);
    err_execution_failure_conditional(ERR == refresh(),
                                      "Error refreshing ncurses window.");
}

void emulate_setcursor(int y, int x) {
//    setsyx(y, x);
    check_terminal_area_access(y, x);
    move(y, x);
    err_execution_failure_conditional(ERR == refresh(),
                                      "Error refreshing ncurses window.");
}

