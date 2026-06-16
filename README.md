# AsCore Operating System

AsCore is a lightweight, custom open-source operating system written from scratch in x86 Assembly. This project aims to demonstrate low-level system architecture, bootloader mechanics, and kernel development principles.

Currently, AsCore successfully boots into 16-bit Real Mode, initializes segment registers for architectural safety, and prints a welcome string directly to the screen using BIOS Teletype Interrupts (`INT 0x10`).

## Prerequisites

To compile and emulate AsCore, you need to have `nasm` (Netwide Assembler) and `qemu` installed on your system. 

If you are on **Arch Linux**, you can install them via pacman:
```bash
sudo pacman -S nasm qemu-desktop
```

## How to Build and Run

Follow these simple steps to compile the source code and run it inside the QEMU emulator:
1. Compile the Source

We use nasm to compile the raw Assembly file into a pure 512-byte binary boot sector:
```bash

nasm -f bin boot.asm -o boot.bin
```
2. Run with QEMU

Once the boot.bin is generated, you can boot it directly using the QEMU x86 emulator:

```bash
qemu-system-i386 -drive format=raw,file=boot.bin
```
## Project Roadmap

    [x] Create a 512-byte Boot Sector with Magic Number (0xAA55)

    [x] Implement a custom String Printing Function via BIOS Interrupts (Null-terminated)

    [ ] Read additional sectors from disk (INT 0x13)

    [ ] Transition from 16-bit Real Mode to 32-bit Protected Mode

    [ ] Initialize the Global Descriptor Table (GDT)

## License

This project is open-source and available under the GPL-3.0 License.

