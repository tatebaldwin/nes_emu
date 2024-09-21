#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "rom.h"

struct rom_data* parse_rom(char* filename)
{
  struct rom_data* r;
  r = malloc(sizeof(struct rom_data));
  FILE* f;
  f = fopen(filename, "rb");
  if (!f)
    return NULL;
  char header[16];
  fread(header, sizeof(byte), 16, f);
  if (header[0] == 0x4E && header[1] == 0x45 &&
      header[2] == 0x53 && header[3] == 0x1A)
    { // is ines
      r->format = header[7];
      r->mapper = header[8];
      r->prg_size = header[4] * 16384;
      r->chr_size = header[5] * 8192;
    }
  else
  {
    return NULL;
  }
  fclose(f);
  return r;
}
