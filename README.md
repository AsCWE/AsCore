# AsCore Operating System 🚀

AsCore is a hobbyist x86 operating system built from scratch, focusing on low-level system architecture, custom bootloader pipelines, and direct hardware manipulation. The project transitions from pure Assembly into a 16-bit Real Mode C environment to leverage structured kernel development.

---

## 🗺️ System Architecture & Memory Map

To ensure maximum efficiency and prevent hardware memory corruption, AsCore utilizes a carefully optimized segment layout within the 1 MB Real Mode boundaries:

| Memory Address Range | Size | Usage / Purpose | Status |
| :--- | :--- | :--- | :--- |
| **`0x00000 - 0x003FF`** | 1 KB | Interrupt Vector Table (IVT) | **Reserved by BIOS** |
| **`0x00400 - 0x004FF`** | 256 B | BIOS Data Area (BDA) | **Reserved by BIOS** |
| **`0x00500 - 0x07BFF`** | ~30 KB | Safe Custom Stack Area (Grows Downwards) | **Active (Secured)** |
| **`0x07C00 - 0x07DFF`** | 512 B | Main Boot Sector (`boot.asm`) | **Loaded by BIOS** |
| **`0x07E00 - 0x7FFFF`** | ~480 KB | **Conventional Kernel Memory Space** | **Active (`kernel.c`)** |
| **`0xB8000 - 0xBFFFF`** | 32 KB | VGA Text Mode Video Memory (Color Buffer) | **Direct Hardware I/O** |

---

## 🛠️ Compilation & Build Pipeline

The modern GCC toolchain forces Position Independent Executable (PIE) and Global Offset Tables (GOT) by default. AsCore uses specific compiler flags to bypass these mechanisms, producing raw, position-dependent 16-bit binary files.

### Compilation Workflow
1. **Bootloader Compilation:** Compiles `boot.asm` into a 512-byte raw binary master boot record (MBR).
2. **Kernel Compilation:** Compiles `kernel.c` with 16-bit GCC inline directives, disabling the standard library (`-ffreestanding`) and stripping position-independent code attributes (`-fno-pie`, `-fno-pic`).
3. **Linker Optimization:** Links `kernel.o` using `ld` at the explicit text offset of `0x7E00` matching the bootloader's jump address.
4. **Image Flattening:** Merges binaries into a unified `1.44 MB` Floppy Disk Image (`ascore.img`) utilizing structured `dd` seeking blocks.

---

## 🚀 How to Run

### Prerequisites
Make sure you have `nasm`, `gcc`, `ld`, and `qemu` installed on your host system (e.g., Arch Linux toolchain).

### Automated Execution
Run the custom automated pipeline script to compile everything and fire up the QEMU emulator:

```bash
chmod +x build.sh
./build.sh
```
## 📅 Roadmap & Current Status

    [x] Write custom 16-bit Real Mode MBR Bootloader.

    [x] Implement robust BIOS CHS Floppy Disk sector reading.

    [x] Isolate and secure Safe Stack Memory Range to prevent memory corruption.

    [x] Configure 16-bit modern GCC toolchain cross-compilation pipeline.

    [x] Implement low-level Screen Clearing Loop utilizing direct 0xB8000 VGA pointer overrides.

    [ ] Implement advanced VGA hardware port driver (0x3D4 / 0x3D5 Outbound Tracking).

    [ ] Design custom printf implementation for structured text output.

    [ ] Transition from 16-bit Real Mode to 32-bit Protected Mode (GDT setup).
    ```
   ## 📄 License

This project is open-source and available under the GPL-3.0 License.
