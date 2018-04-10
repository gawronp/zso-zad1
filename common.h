#ifndef _COMMON_H_
#define _COMMON_H_

void copy_to_host(pid_t pid, void *start_local, void *start_remote, int length);

void copy_to_guest(pid_t pid, void *start_local, void *start_remote,
                   int length);

struct user_regs_struct get_registers(pid_t pid);

void set_return_value_reg(pid_t pid, unsigned long long int val);

#endif