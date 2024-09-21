#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "6502.h"
#include "famicom.h"
#include "rom.h"

union Famicom famicom;
bool debug = true;

int main(int argc, char** argv)
{
  if (argc < 2)
  {
      printf("nemu [file]\n");
      return 1;
  }
  famicom.cpu = malloc(sizeof(struct cpu_6502));
  if (famicom.cpu == NULL)
    return 1;
  struct rom_data* r;
  r = parse_rom(argv[1]);
  if (!r)
  {
    free(famicom.cpu);
    printf("error opening file\n");
    return 1;
  }
  
  if (debug)
  {
    printf("%s\n", argv[1]);
    printf("format %d, mapper %d\nprg: %d, chr: %d\n", r->format, r->mapper, r->prg_size, r->chr_size);
  }
  cpu_6502_debug(famicom.cpu);
  free(r);
  free(famicom.cpu);
  return 0;
}


