# AsCore 🚀

A minimalist, bare-metal microkernel built from scratch for the 32-bit RISC-V (`RV32`) architecture. Designed to run on the QEMU virtual machine (`virt` board), **AsCore** serves as a lightweight playground for systems programming, hardware-software co-design, and microkernel architecture exploration.

---

## 🛠️ Features

* **Bare-Metal Bootstrapping:** Custom assembly startup code (`boot.S`) initializing the stack, global pointers, and CPU delegation.
* **Vector Interrupt & Trap Handling:** Hand-crafted assembly vector table (`trap.S`) with full context save/restore, dispatching to a centralized C-based `trap_handler`.
* **System Call Support:** Support for synchronous exceptions (`ecall` / environment calls from Machine-mode) with instruction program counter (`mepc`) adjustment.
* **16550A UART Driver:** Custom polling and interrupt-driven Serial driver mapped via MMIO at `0x10000000`.
* **PLIC Integration (WIP):** Target-specific Platform-Level Interrupt Controller configuration to route external keyboard and hardware interrupts.
* **VGA Driver Module:** Native low-level VGA driver support for visual framebuffer output.

---

## 📁 Project Structure

```text
AsCore/
├── boot.S          # Assembly entry point (entry, setup stack, vector registration)
├── trap.S          # Low-level trap vector (context save/restore, csrr/csrw)
├── trap.c          # C trap handler (decodes mcause, handles ecalls & interrupts)
├── kernel.c        # Kernel main entry point, PLIC/UART initialization, main loop
├── uart.c/h        # 16550A UART driver for console I/O
├── link.ld         # Linker script mapping the physical memory (loads at 0x80000000)
└── build.sh        # Automation script for building and running on QEMU
```
## 🚀 Getting Started
To compile and run AsCore, you need the RISC-V GNU Toolchain and QEMU installed on your host system.
On Arch Linux:
```bash
sudo pacman -S riscv64-unknown-elf-gcc riscv64-unknown-elf-binutils qemu-system-riscv
```
## ⚖️ License

Distributed under the AsCWE Transparency and Source-Available License. See LICENSE for more information.
