CC := cc
all: nes_emu
nes_emu:
	cc -o bin/nes_emu main.c 6502.c rom.c famicom.c
clean:
	rm -f bin/*

