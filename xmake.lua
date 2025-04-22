-- Project settings
set_project('demo')
set_version('0.1')
set_license('GPL-3.0')
set_languages('gnu23')
set_warnings('everything')

set_policy('check.auto_ignore_flags', false)

includes('cross_files/options.lua')
includes('cross_files/dynamic_lds.lua')
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

    -- Add source files
    add_files('src/**.c', 'src/**.s')
    add_includedirs('src')

    -- on_load(function (target) 
    --     target:add('files', path.join(target:targetdir(), 'linker_new.ld'))
    -- end)

    on_load(function (target)
        -- generate linker file
        target:set('configdir', target:targetdir())
        target:add('configfiles', 'linker_sct/linker_new.ld.in')

        -- add linker file to ldflags
        target:add('ldflags', '-T' .. path.join(target:targetdir(), 'linker_new.ld'))
        target:data_add('linkdepfiles', path.join(target:targetdir(), 'linker_new.ld'))

        -- add map file
        target:add('ldflags', '-Wl,-Map,' .. path.join(target:targetdir(), target:name() .. '.map'))
    end)

    -- Add dependencies
    add_deps('embed-utils', 'STM32_StdLib')
    add_linkgroups('embed-utils', {whole = true})

    -- custom rules for objdump and size
    after_build(function(target)
        local builddir = target:targetdir()
        local elf_file = target:targetfile()
        local elf_name = target:name()

        os.runv(
            '$(toolchain)-objcopy',
            {'-O', 'binary', elf_file, path.join(builddir, elf_name .. '.bin')}
        )

        os.runv(
            '$(toolchain)-objdump', 
            {'-Sd', '--visualize-jumps', elf_file}, 
            {stdout = path.join(builddir, elf_name .. '.s')}
        )

        os.execv('$(toolchain)-size', {elf_file})
    end)
