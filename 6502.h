struct cpu_6502
{
  word pc;
  byte reg[5];
  byte* ram;
};

enum cpu_6502_registers
{
  reg_a,
  reg_x,
  reg_y,
  reg_s,
  reg_sr
};

enum get_or_set
{
  get,
  set
};

enum cpu_6502_a
{
  a, imp, imm, abs_, zp, rel,
  abs_i, abs_x, abs_y,
  zp_i_x, zp_i_y, zp_ii_x, zp_ii_y,
};

enum cpu_6502_mnemonics
{
  ADC,AND,ASL,BCC,BCS,BEQ,BIT,BMI,BNE,BPL,BRK,BVC,BVS,CLC,
  CLD,CLI,CLV,CMP,CPX,CPY,DEC,DEX,DEY,EOR,INC,INX,INY,JMP,
  JSR,LDA,LDX,LDY,LSR,NOP,ORA,PHA,PHP,PLA,PLP,ROL,ROR,RTI,
  RTS,SBC,SEC,SED,SEI,STA,STX,STY,TAX,TAY,TSX,TXA,TXS,TYA,
  Unimplemented
};

typedef struct op_6502
{
  enum cpu_6502_mnemonics o;
  enum cpu_6502_a a;
  byte opcode;
} op_6502;

byte cpu_6502_reg(struct cpu_6502* cpu, enum cpu_6502_registers r, enum get_or_set g, byte value);
void cpu_6502_debug(struct cpu_6502* cpu);
op_6502 cpu_6502_op_decode(byte opcode);
void cpu_6502_op(struct cpu_6502* cpu, op_6502 op);
