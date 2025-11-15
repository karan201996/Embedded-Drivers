MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
    .text :
    {
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)
        KEEP(*(.init))
        KEEP(*(.fini))
    } > FLASH

    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH

    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    } > FLASH

    .data : AT (ADDR(.text) + SIZEOF(.text))
    {
        _sdata = .;
        __data_start__ = .;
        *(.data*)
        __data_end__ = .;
        _edata = .;
    } > SRAM

    .bss (NOLOAD) :
    {
        __bss_start__ = .;
        _sbss = .;
        *(.bss*)
        *(COMMON)
        __bss_end__ = .;
        _ebss = .;
    } > SRAM

    .stack (NOLOAD):
    {
        . = ALIGN(8);
    } > SRAM
}

PROVIDE(_sidata = LOADADDR(.data));
