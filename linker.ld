OUTPUT_ARCH( "riscv" )
ENTRY( _start )

SECTIONS
{
  /* Kodun tam olarak QEMU'nun uyandığı adreste başlamasını GARANTİLİYORUZ */
  . = 0x80000000;

  .text : {
    boot.o(.text.init)  /* İlk komutun boot.o içindeki _start olmasını zorluyoruz */
    *(.text.init)
    *(.text .text.*)
  }

  .rodata : {
    *(.rodata .rodata.*)
  }

  .data : {
    *(.data .data.*)
  }

  .bss : {
    *(.bss .bss.*)
    *(COMMON)
  }

  /* Stack alanını hizalayıp sona koyuyoruz */
  . = ALIGN(16);
  . += 0x4000; /* 16 KB Stack alanı */
  stack_top = .;
}
