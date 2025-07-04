ENTRY(loader)                                         /* the name of the entry label */

SECTIONS {
    . = 0x00100000;                                   /* code loads at 1 MB */

    /* Multiboot header debe ir primero */
    .multiboot :
    {
        *(.multiboot)
    }

    .text ALIGN(0x1000) :
    {
        *(.text)
    }

    .rodata ALIGN(0x1000) :
    {
        *(.rodata*)
    }

    .data ALIGN(0x1000) :
    {
        *(.data)
    }

    .bss ALIGN(0x1000) :
    {
        *(.bss)
        *(COMMON)
    }
}