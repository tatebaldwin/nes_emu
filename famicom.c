#include "types.h"
#include "famicom.h"

enum Famicom_mmap Famicom_mmap_get(word addr)
{
  if (addr < 0x0800)
    return fc_ram;
  else if (0x07FF < addr && addr < 0x2000)
    return fc_ram_mirrored;
  else if (0x1FFF < addr && addr < 0x2008)
    return fc_ppu;
  else if (0x2007 < addr && addr < 0x4000)
    return fc_ppu_mirrored;
  else if (0x3FFF < addr && addr < 0x4018)
    return fc_apu;
  else if (0x4017 < addr && addr < 0x4020)
    return fc_test;
  else if (0x401F < addr)
    return fc_cartridge;
}

byte Famicom_mem (union Famicom* famicom, word addr, enum get_or_set g, byte value)
{
  enum Famicom_mmap mmap;
  mmap = Famicom_mmap_get(addr);
  switch(mmap)
  {
  case fc_ram:
    if (g == get)
      return famicom->ram[addr];
    else if (g == set)
      famicom->ram[addr] = value;
    break;
  case fc_ram_mirrored:
    if (g == get)
      return famicom->ram[addr&0x00FF];
    else if (g == set)
      famicom->ram[addr&0x00FF] = value;
    break;
  case fc_ppu:
    if (g == get)
      return famicom->ppureg[(addr&0xF)%9];
    else if (g == set)
      famicom->ppureg[(addr&0xF)%9] = value;
    break;
  case fc_ppu_mirrored:
    if (g == get)
      return famicom->ppureg[(addr&0xF)%9];
    if (g == set)
      famicom->ppureg[(addr&0xF)%9] = value;
  case fc_apu:
    
  }
}
