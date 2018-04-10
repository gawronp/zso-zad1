#include <elf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "elf.h"

#include "alienos.h"
#include "error.h"

struct section_info get_params_section_info(const char *elf_path) {
  struct section_info params_info;
  params_info.memory_addr = 0;
  params_info.length_bytes = 0;

  FILE *elf_file = fopen(elf_path, "r");
  if (elf_file == NULL) {
    CALL_ERR("Cannot open alien program file")
  }

  Elf64_Ehdr elf_hdr;
  fread(&elf_hdr, 1, sizeof(elf_hdr), elf_file);
  if (elf_hdr.e_ident[EI_MAG0] != ELFMAG0 ||
      elf_hdr.e_ident[EI_MAG1] != ELFMAG1 ||
      elf_hdr.e_ident[EI_MAG2] != ELFMAG2 ||
      elf_hdr.e_ident[EI_MAG3] != ELFMAG3 ||
      elf_hdr.e_ident[EI_CLASS] != ELFCLASS64 ||
      elf_hdr.e_ident[EI_DATA] != ELFDATA2LSB ||
      elf_hdr.e_ident[EI_VERSION] != EV_CURRENT ||
      elf_hdr.e_ident[EI_OSABI] != ELFOSABI_NONE) {
    SIMPLE_ERR("Elf header incorrect!");
  }
  if (elf_hdr.e_type != ET_EXEC) {
    SIMPLE_ERR("Provided elf file is not of type ET_EXEC!");
  }
  if (elf_hdr.e_phentsize != sizeof(Elf64_Phdr)) {
    SIMPLE_ERR(
        "Elf header of alien program contains program header size != proper "
        "elf 64 program header size");
  }

  Elf64_Phdr phdr;
  bool found_pt_params = false;
  for (int i = 0; i < elf_hdr.e_phnum; i++) {
    if (0 != fseek(elf_file, elf_hdr.e_phoff + i * sizeof(phdr), SEEK_SET)) {
      CALL_ERR("Fseek call resulted in error");
    }
    fread(&phdr, 1, sizeof(phdr), elf_file);
    if (phdr.p_type == PT_PARAMS) {
      if (!found_pt_params) {
        params_info.memory_addr = phdr.p_vaddr;
        params_info.length_bytes = phdr.p_memsz;
        found_pt_params = true;
      } else {
        SIMPLE_ERR("There are multiple PT_PARAMS sections in alien program!");
      }
    }
    if (phdr.p_type == PT_INTERP) {
      SIMPLE_ERR("There is a PT_INTERP section in alien program!");
    }
  }

  if (EOF == fclose(elf_file)) {
    CALL_ERR("Cannot close alien program file");
  }

  return params_info;
}