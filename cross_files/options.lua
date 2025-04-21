includes('memory_map.lua')

set_toolchains('$(toolchain)')

option('toolchain')
    set_default('arm-none-eabi')
    set_description('select compile toolchain')

option('stack_size')
    set_default('0x400')
    set_configvar('stack_size', '$(stack_size)')

option('memory_map')
    set_default('flash_ram')
    set_values(memory_map_names)

    local map = memory_map[get_config('memory_map')]

    if map then
        add_defines(map.defines, {public = true})

        set_configvar('REGION_BOOT', map.REGION_BOOT)
        set_configvar('REGION_TEXT', map.REGION_TEXT)
        set_configvar('REGION_TEXT_AT', map.REGION_TEXT_AT)
        set_configvar('REGION_RODATA', map.REGION_RODATA)
        set_configvar('REGION_RODATA_AT', map.REGION_RODATA_AT)
        set_configvar('REGION_STACK', map.REGION_STACK)
        set_configvar('REGION_DATA', map.REGION_DATA)
        set_configvar('REGION_DATA_AT', map.REGION_DATA_AT)
        set_configvar('REGION_BSS', map.REGION_BSS)
    end

option_end()
