-- Project settings
set_project('demo')
set_version('0.1')
set_license('GPL-3.0')
set_languages('gnu23')
set_warnings('everything')

set_policy('check.auto_ignore_flags', false)
set_policy('build.always_update_configfiles', true)

includes('cross_files/options.lua')
includes('cross_files/generate_rules.lua')
includes('cross_files/toolchain.lua')

-- Global configurations
add_rules('mode.debug', 'mode.release')
set_defaultmode('debug')
set_defaultplat('cross')
set_defaultarchs('arm')

includes('subprojects/embed-utils')
includes('subprojects/STM32_StdLib')

add_cxflags(
    '-mcpu=cortex-m3',
    '-ftree-vectorize',
    '-mthumb',
    '-mabi=aapcs',
    '-fdata-sections',
    '-ffunction-sections'
)

add_asflags(
    '-mthumb',
    '-mcpu=cortex-m3',
    '-x assembler-with-cpp'
)

add_ldflags(
    '-mcpu=cortex-m3',
    '-nostartfiles',
    '--specs=nano.specs',
    '-Wl,--gc-sections',
    '-Wl,--print-memory-usage',
    '-lm',
    {force = true}
)

-- Debug mode specific settings
if is_mode('debug') then
    add_cxflags('-Og', '-g3')
end

-- Release mode specific settings
if is_mode('release') then
    add_cxflags('-O2')
end

set_configvar('stack_size', '$(stack_size)')

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

local dev_info = device_table[get_config('target_mcu')]

if dev_info then
    set_configvar('flash_size', dev_info.memory.flash_size)
    set_configvar('ram_size', dev_info.memory.ram_size)
    add_defines('STM32F10X_' .. dev_info.memory.capacity)
end

-- Target configurations
target('demo')
    set_kind('binary')
    set_extension('.elf')

    -- add_options(
    --     'target_mcu',
    --     'stack_size',
    --     'memory_map'
    -- )

    add_rules(
        'generate.extrafiles',
        'generate.sizeinfo',
        'generate.lds'
    )

    -- Add source files
    add_files('src/**.c', 'src/**.s')
    add_includedirs('src')

    -- add linker script template
    add_files('linker_sct/linker_new.ld.in')

    -- Add dependencies
    add_deps('embed-utils', 'STM32_StdLib')
    add_linkgroups('embed-utils', {whole = true})
