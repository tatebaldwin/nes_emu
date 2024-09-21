union Famicom
{
  struct cpu_6502* cpu;
  byte ram[0x0FFF];
  byte ppureg[0x8];
  byte apureg[0x18];
};

enum Famicom_mmap
{
  fc_ram,
  fc_ram_mirrored,
  fc_ppu,
  fc_ppu_mirrored,
  fc_apu,
  fc_test,
  fc_cartridge
};

byte Famicom_mmap_get(union Famicom* famicom, word addr, enum get_or_set g);
