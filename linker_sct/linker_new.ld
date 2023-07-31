OUTPUT_ARCH(arm)
ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx) : ORIGIN = @flash_base@, LENGTH = @flash_size@ 
    RAM (wx) : ORIGIN = @ram_base@, LENGTH = @ram_size@
}

PHDRS
{
    isr_table PT_LOAD;
    text PT_LOAD;
    data PT_LOAD;
    rodata PT_LOAD;
}

SECTIONS
{
    .boot : {
        . = ALIGN(4);
        PROVIDE(__sisr_vector = .);
        KEEP(*(.isr_vector));
        PROVIDE(__eisr_vector = .);
    } > FLASH :isr_table

    .text : {
        . = ALIGN(4);
        PROVIDE(__stext = .);
        *(.text)
        *(.text.*)
        *(.text*)

        PROVIDE(__sctor = .);
        *(.ctors)
        PROVIDE(__ector = .);

        PROVIDE(__sdtor = .);
        *(.dtors)
        PROVIDE(__edtor = .);

        PROVIDE(__etext = .);
    } > FLASH :text

    .rodata : {
        . = ALIGN(4);
        PROVIDE(__load_start = .);
        PROVIDE(__srodata = .);
        *(.rodata)
        *(.rodata.*)
        *(.rodata*)
        PROVIDE(__erodata = .);
    } > RAM AT > FLASH :rodata

    PROVIDE(__load_addr = LOADADDR(.rodata));

    .data : {
        . = ALIGN(4);
        PROVIDE(__sdata = .);
        *(.data)
        *(.data.*)
        *(.data*)
        PROVIDE(__edata = .);
        PROVIDE(__load_end = .);
    } > RAM AT > FLASH :data

    .bss (NOLOAD) : {
        . = ALIGN(4);
        PROVIDE(__sbss = .);
        *(.bss)
        *(.bss.*)
        *(.bss*)
        *(COMMON)
        PROVIDE(__ebss = .);
    } > RAM AT > RAM

    PROVIDE(__stack = @ram_base@ + @ram_size@);
}
