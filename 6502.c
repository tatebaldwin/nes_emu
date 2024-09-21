#include "types.h"
#include "6502.h"
#include <stdio.h>

op_6502 cpu_6502_opcodes[] =
{
  {Unimplemented, imp, -1},
  {ADC,imm,0x69}, {ADC,zp,0x65}, {ADC,zp_i_x,0x35},
  {ADC,abs_,0x2D}, {ADC,abs_x,0x3D}, {ADC,abs_y,0x79},
  {ADC,zp_ii_x,0x61}, {ADC,zp_ii_y, 0x71},
  {AND,imm,0x29}, {AND,zp,0x25}, {AND,zp_i_x,0x35},
  {AND,abs_,0x2D}, {AND,abs_x,0x3D}, {AND,abs_y,0x39},
  {AND,zp_ii_x,0x21},{AND,zp_ii_y,0x31},
  {ASL,a,0x0A}, {ASL,zp,0x06}, {ASL,zp_i_x,0x16},
  {ASL,abs_,0x0E},{ASL,zp_i_x,0x16},{ASL,abs_x,0x1E},
  {BCC,rel,0x90},{BCS,rel,0xB0},{BEQ,rel,0xF0},
  {BIT,zp,0x24},{BIT,abs_,0x2C},{BMI,rel,0x30},
  {BNE,rel,0xD0},{BPL,rel,0x10},{BRK,imp,0x00},
  {BVC,rel,0x50},{BVS,rel,0x70},{CLC,imp,0x18},
  {CLD,imp,0xD8},{CLI,imp,0x58},{CLV,imp,0xB8},
  {CMP,imm,0xC9},{CMP,zp,0xC5},{CMP,zp_i_x,0xD5},
  {CPX,imm,0xE0},{CPX,zp,0xE4},{CPX,abs_,0xEC},
  {CPY,imm,0xC0},{CPY,zp,0xC4},{CPY,abs_,0xCC},
  {DEC,zp,0xC6},{DEC,zp_i_x,0xD6},{DEC,abs_,0xCE},
  {DEC,abs_x,0xDE},{DEX,imp,0xCA},{DEY,imp,0x88},
  {EOR,imm,0x49},{EOR,zp,0x45},{EOR,zp_i_x,0x55},
  {EOR,abs_,0x4d},{EOR,abs_x,0x45},{EOR,abs_y,0x59},
  {EOR,zp_ii_x,0x41},{EOR,zp_ii_y,0x51},
  {INC,zp,0xE6},{INC,zp_i_x,0xF6},{INC,abs_,0xEE},
  {INC,abs_x,0xFE},{INX,imp,0xE8},{INY,imp,0xC8},
  {JMP,abs_,0x4C},{JMP,abs_i,0x6C},{JSR,abs_,0x20},
  {LDA,imm,0xA9},{LDA,zp,0xA5},{LDA,zp_i_x,0xB5},
  {LDA,abs_,0xAD},{LDA,abs_x,0xBD},{LDA,abs_y,0xB9},
  {LDA,zp_ii_x,0xA1},{LDA,zp_ii_y,0xB1},{LDX,imm,0xA2},
  {LDX,zp,0xA6},{LDX,zp_i_y,0xB6},{LDX,abs_,0xAE},
  {LDX,abs_y,0xBE},{LDY,imm,0xA0},{LDY,zp,0xA4},
  {LDY,zp_i_x,0xB4},{LDY,abs_,0xAC},{LDY,abs_x,0xBC},
  {LSR,a,0x4A},{LSR,zp,0x46},{LSR,zp_i_x,0x56},
  {LSR,abs_,0x4E},{LSR,abs_x,0x5E},{NOP,imp,0xEA},
  {ORA,imm,0x09},{ORA,zp,0x05},{ORA,zp_i_x,0x15},
  {ORA,abs_,0x0D},{ORA,abs_x,0x1D},{ORA,abs_y,0x19},
  {ORA,zp_ii_x,0x01},{ORA,zp_ii_y,0x11},{PHA,imp,0x48},
  {PHP,imp,0x08},{PLA,imp,0x68},{PLP,imp,0x28},
  {ROL,a,0x2A},{ROL,zp,0x26},{ROL,zp_i_x,0x36},
  {ROL,abs_,0x2E},{ROL,abs_x,0x3E},{ROR,a,0x6A},
  {ROR,zp,0x66},{ROR,zp_i_x,0x76},{ROR,abs_,0x6E},
  {ROR,abs_x,0x7E},{RTI,imp,0x40},{RTS,imp,0x60},
  {SBC,imm,0xE9},{SBC,zp,0xE5},{SBC,zp_i_x,0xF5},
  {SBC,abs_,0xED},{SBC,abs_x,0xFD},{SBC,abs_y,0xF9},
  {SBC,zp_ii_x,0xE1},{SBC,zp_ii_y,0xF1},{SEC,imp,0x38},
  {SED,imp,0xF8},{SEI,imp,0x78},{STA,zp,0x85},
  {STA,zp_i_x,0x95},{STA,abs_,0x8D},{STA,abs_x,0x9D},
  {STA,abs_y,0x99},{STA,zp_ii_x,0x81},{STA,zp_ii_y,0x91},
  {STX,zp,0x86},{STX,zp_i_y,0x96},{STX,abs_,0x8E},
  {STY,zp,0x84},{STY,zp_i_x,0x94},{STY,abs_,0x8C},
  {TAX,imp,0xAA},{TAY,imp,0xA8},{TSX,imp,0xBA},
  {TXA,imp,0x8A},{TXS,imp,0x9A},{TYA,imp,0x98}
};

byte cpu_6502_reg(struct cpu_6502* cpu, enum cpu_6502_registers r, enum get_or_set g, byte value)
{
  switch(g)
  {
  case get:
    return cpu->reg[r];
    break;
  case set:
    cpu->reg[r] = value;
    break;
  }
}

void cpu_6502_debug(struct cpu_6502* cpu)
{
  printf("A X Y S SR\n");
  for (int i=0; i<5; i++)
    {
      printf("%0X ", cpu->reg[i]);
    }
  printf("\n");
  printf("PC: %X ", cpu->pc);
  printf("\n");
}

op_6502 cpu_6502_op_decode(byte opcode)
{
  for (int i=0; i<sizeof(op_6502)*sizeof(cpu_6502_opcodes);i++)
    {
      if (cpu_6502_opcodes[i].opcode == opcode)
	return cpu_6502_opcodes[i];
    }
  return cpu_6502_opcodes[0]; // Unimplemented
}

void cpu_6502_op(struct cpu_6502* cpu, op_6502 op)
{
  switch(op.o)
  {
  case ADC:
    break;
  }
}
