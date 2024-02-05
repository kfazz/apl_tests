#!/bin/bash
sdcc --codeseg .text --constseg .apl --out-fmt-elf --asm=gas -mz180  -S test2.c
z80-elf-as -march=z180 -sdcc test2.asm
z80-elf-ld -o test2.elf -T ./script.ld a.out
z80-elf-objcopy -v -O binary --set-section-flags .apl=alloc,load,data test2.elf test2.apl
rm test2.img
mkfs.msdos -C test2.img 720
mcopy -i test2.img test2.apl ::test2.apl
