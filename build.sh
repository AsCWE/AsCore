#!/bin/bash

echo "[+] Compiling Bootloader"
nasm -f bin boot.asm -o boot.bin

echo "[+] Compiling Kernel Entry..."
nasm -f elf32 entry.asm -o kernel_entry.o

echo "[+] Compiling kernel..."
gcc -m16 -ffreestanding -fno-pie -fno-pic -fno-asynchronous-unwind-tables -march=i386 -c kernel.c -o kernel.o
gcc -m16 -ffreestanding -fno-pie -fno-pic -fno-asynchronous-unwind-tables -march=i386 -c io.c -o io.o
gcc -m16 -ffreestanding -fno-pie -fno-pic -fno-asynchronous-unwind-tables -march=i386 -c vga.c -o vga.o

echo "[+] Linking binaries..."
ld -m elf_i386 -Ttext 0x7E00 -e _start --oformat binary -nostdlib kernel_entry.o kernel.o vga.o io.o -o kernel.bin

echo "[+] Creating 1.44 MB Floppy image..."
dd if=/dev/zero of=ascore.img bs=1024 count=1440
dd if=boot.bin of=ascore.img conv=notrunc
dd if=kernel.bin of=ascore.img bs=512 seek=1 conv=notrunc

echo "[+] Build complete. Initializating QEMU..."
qemu-system-i386 -fda ascore.img
