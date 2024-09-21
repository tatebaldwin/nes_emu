struct rom_data
{
  int format;
  int mapper;
  int prg_size;
  int chr_size;  
};

struct rom_data* parse_rom(char* filename);
