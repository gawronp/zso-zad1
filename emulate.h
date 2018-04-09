#ifndef _EMULATE_H_
#define _EMULATE_H_

#define SYSCALL_END 0
#define SYSCALL_GETRAND 1
#define SYSCALL_GETKEY 2
#define SYSCALL_PRINT 3
#define SYSCALL_SETCURSOR 4

#define CHAR_MASK 0x00ff

#define EXIT_CODE_MIN 0
#define EXIT_CODE_MAX 63

#define MIN_PRINTABLE_CHAR_ASCII_VAL 0x20
#define MAX_PRINTABLE_CHAR_ASCII_VAL 0x7e

void emulate_end(int status);

uint32_t emulate_getrand();

int emulate_getkey();

void emulate_print(int y, int x, uint16_t *chars, int n);

void emulate_setcursor(int y, int x);

#endif