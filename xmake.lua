-- Project settings
set_project('demo')
set_version('0.1')
set_license('GPL-3.0')
set_languages('gnu23')
set_warnings('everything')

set_policy('check.auto_ignore_flags', false)

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

add_options(
    'target_mcu',
    'stack_size',
    'memory_map'
)

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

-- Target configurations
target('demo')
    set_kind('binary')
    set_extension('.elf')

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
