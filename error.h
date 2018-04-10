#ifndef _ERROR_H_
#define _ERROR_H_

#include <err.h>
#include <stdbool.h>
#include <stdnoreturn.h>
#include <stdio.h>

#define ERROR_EMU 127

// asserts call result is not equal to retval, otherwise prints error message
// and quits
#define CALL_NEQ(retval, call)                                     \
  if ((retval) == (call)) {                                        \
    errx(ERROR_EMU, #call " failed in %s:%d", __FILE__, __LINE__); \
  }

// asserts call result is not equal to retval, otherwise prints error message,
// errno information and quits
#define CALL_NEQ_ERRNO(retval, call)                              \
  if ((retval) == (call)) {                                       \
    err(ERROR_EMU, #call " failed in %s:%d", __FILE__, __LINE__); \
  }

// gets called when error occured
#define SIMPLE_ERR(message) \
  errx(ERROR_EMU, #message " in %s:%d", __FILE__, __LINE__);

// gets called when errno is set
#define CALL_ERR(message) \
  err(ERROR_EMU, #message " in %s:%d ", __FILE__, __LINE__);

noreturn void err_invalid_syscall_num(const int syscall_id);

noreturn void err_unknown_key(const int key_ncurses_val);

noreturn void err_unknown_exit_code(const int exit_code);

#endif