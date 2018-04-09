#ifndef _ELF_H_
#define _ELF_H_

struct section_info {
    unsigned long memory_addr;
    unsigned long length_bytes;
};

struct section_info get_params_section_info(const char *elf_path);

#endif