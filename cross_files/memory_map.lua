memory_map_names = {
    'ram_only', 'flash_ram', 'external_ram_only'
}

memory_map = {
    ram_only = {
        REGION_BOOT = 'RAM',

        REGION_TEXT = 'RAM',
        REGION_TEXT_AT = 'RAM',

        REGION_RODATA = 'RAM',
        REGION_RODATA_AT = 'RAM',

        REGION_STACK = 'RAM',

        REGION_DATA = 'RAM',
        REGION_DATA_AT = 'RAM',

        REGION_BSS = 'RAM',

        defines = {'VECT_TAB_SRAM'}
    },

    flash_ram = {
        REGION_BOOT = 'FLASH',

        REGION_TEXT = 'FLASH',
        REGION_TEXT_AT = 'FLASH',

        REGION_RODATA = 'FLASH',
        REGION_RODATA_AT = 'FLASH',

        REGION_STACK = 'RAM',

        REGION_DATA = 'RAM',
        REGION_DATA_AT = 'FLASH',

        REGION_BSS = 'RAM'
    },

    external_ram_only = {
        REGION_BOOT = 'FSMC',

        REGION_TEXT = 'FSMC',
        REGION_TEXT_AT = 'FSMC',

        REGION_RODATA = 'FSMC',
        REGION_RODATA_AT = 'FSMC',

        REGION_STACK = 'FSMC',

        REGION_DATA = 'FSMC',
        REGION_DATA_AT = 'FSMC',

        REGION_BSS = 'FSMC'
    },
}
