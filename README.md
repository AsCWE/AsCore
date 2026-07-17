# AsCore 🚀

A minimalist, hobbyist microkernel built from the ground up for the RISC-V architecture.

---

## 📸 Preview

![AsCore Shell Boot Preview](screenshot.png)

---

## ✨ Features

* **Architecture:** 32-bit RISC-V (`RV32I`)[cite: 4].
* **Environment:** 100% Bare-metal development (No standard library, no host OS dependencies)[cite: 7].
* **Modular Codebase:** Clean separation between kernel core, hardware drivers, interrupts, and shell[cite: 5].
* **Hardware Support:** Custom UART driver for serial communication and PLIC-based keyboard interrupts[cite: 3].
* **Interactive Shell:** ANSI-colored, responsive command-line interface directly running on hardware[cite: 4].

---

## 🛠️ Project Structure

* `boot.S` - Assembly entry point and bootstrap loader.
* `trap.S` / `trap.c` - Low-level interrupt and exception handlers[cite: 3, 7].
* `kernel.c` - Core initialization routines and hardware provisioning[cite: 1].
* `shell.c` / `shell.h` - Interactive user interface and command parsers[cite: 4, 5].
* `uart.c` / `uart.h` - Serial communication drivers[cite: 2, 6].

---

## 🚀 How to Run

### Prerequisites
You need the RISC-V toolchain (`riscv64-elf-gcc`, `riscv64-elf-ld`) and `qemu-system-riscv32` installed on your system[cite: 7].

### Build and Emulate
Simply run the compilation script to build the microkernel and launch it inside QEMU:

```bash
chmod +x build.sh
./build.sh
```


## ⚖️ License

Distributed under the AsCWE Transparency and Source-Available License. See LICENSE for more information.
