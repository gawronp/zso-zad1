#ifndef _ELF_H_
#define _ELF_H_

#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "alienos.h"
#include "error.h"

struct section_info {
    unsigned long memory_addr;
    unsigned long length_bytes;
};


struct section_info get_params_section_info(const char *elf_path) {
    struct section_info params_info;
    params_info.memory_addr = 0;
    params_info.length_bytes = 0;

    FILE * elf_file = fopen(elf_path, "r");
    Elf64_Ehdr elf_hdr;
    fread(&elf_hdr, 1, sizeof(elf_hdr), elf_file);
    Elf64_Phdr phdr;
    bool found_pt_params = false;
    for (int i = 0; i < elf_hdr.e_phnum; i++) {
        fseek(elf_file, elf_hdr.e_phoff + i * sizeof(phdr), SEEK_SET);
        fread(&phdr, 1, sizeof(phdr), elf_file);
        if (phdr.p_type == PT_PARAMS) {
            if (!found_pt_params) {
                params_info.memory_addr = phdr.p_vaddr;
                params_info.length_bytes = phdr.p_memsz;
                found_pt_params = true;
            } else {
                err_simple_message("There are multiple PT_PARAMS sections in alien program!");
            }
        }
        if (phdr.p_type == PT_INTERP) {
            // TODO?
            err_simple_message("There is a PT_INTERP section in alien program!");
        }
    }
    fclose(elf_file);

    return params_info;
}

//
//struct section_info get_params_section_info(const char *elf_path) {
//    struct section_info params_section;
//    // TODO: unmock
//
//    params_section.memory_addr = 0x000000003133a6fc;
//    params_section.length_bytes = 0x0000000000000004;
//
//    return params_section;
//}

#endif