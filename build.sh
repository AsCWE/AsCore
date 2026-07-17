#!/bin/bash

set -e

TARGET="riscv64-elf"

echo "=== Compiling ==="

echo "[1/5] Removing old files..."
rm -f *.o kernel.elf
rm -f ./*.o ./*.bin

echo "[2/5] Compiling Assembly sources..."
$TARGET-gcc -march=rv32ima_zicsr -mabi=ilp32 -c boot.S -o boot.o

$TARGET-gcc -march=rv32ima_zicsr -mabi=ilp32 -c trap.S -o trap_asm.o

echo "[3/5] Compiling C sources..."
$TARGET-gcc -march=rv32ima_zicsr -mabi=ilp32 -ffreestanding -nostdlib -c kernel.c -o kernel.o
$TARGET-gcc -march=rv32ima_zicsr -mabi=ilp32 -ffreestanding -nostdlib -c trap.c -o trap.o
$TARGET-gcc -march=rv32ima_zicsr -mabi=ilp32 -ffreestanding -nostdlib -c uart.c -o uart.o
$TARGET-gcc -march=rv32ima_zicsr -mabi=ilp32 -ffreestanding -nostdlib -c shell.c -o shell.o

echo "[4/5] Linking..."
$TARGET-ld -m elf32lriscv -T linker.ld boot.o trap_asm.o trap.o kernel.o uart.o shell.o -o kernel.elf

echo "=== Compilation Success! ==="

echo "[5/5] Initializating QEMU..."
qemu-system-riscv32 -nographic -machine virt -bios none -kernel kernel.elf
# Eehhhh! burayı da AI yazsın Uğraşamam
