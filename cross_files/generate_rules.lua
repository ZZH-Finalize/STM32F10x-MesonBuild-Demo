rule('generate.lds')
    set_extensions('.ld.in', '.lds.in')

    on_config(function (target)
        -- get matched file
        local sourcebatch = target:sourcebatches()['generate.lds']

        if not sourcebatch then
            return
        end

        local source_file = sourcebatch.sourcefiles[#sourcebatch.sourcefiles]
        local output_file, linker_file

        if target:get('configdir') then
            output_file = path.basename(source_file)
            linker_file = path.join(target:get('configdir'), output_file)
        else
            linker_file = path.join(target:targetdir(), path.basename(source_file))
            output_file = path.relative(linker_file, '$(buildir)')
        end

        -- generate linker file
        target:add('configfiles', source_file, {filename = output_file})

        -- add linker file to ldflags
        target:add('ldflags', '-T' .. linker_file)
        target:data_add('linkdepfiles', linker_file)

        target:set('generated_lds', linker_file)
    end)

    after_clean(function (target)
        os.rm(target:get('generated_lds'))
    end)

rule('generate.map')
    on_config(function (target) 
        -- add map file
        target:add('ldflags', '-Wl,-Map,' .. path.join(target:targetdir(), target:name() .. '.map'))
    end)

    after_clean(function (target) 
        os.rm(path.join(target:targetdir(), target:name() .. '.map'))
    end)

rule('generate.bin')
    after_build(function (target) 
        local builddir = target:targetdir()
        local elf_file = target:targetfile()
        local elf_name = target:name()
        local toolchain = target:compiler('cc'):toolchain():fullname() 

        os.runv(
            toolchain .. '-objcopy',
            {'-O', 'binary', elf_file, path.join(builddir, elf_name .. '.bin')}
        )
    end)

    after_clean(function (target) 
        os.rm(path.join(target:targetdir(), target:name() .. '.bin'))
    end)

rule('generate.disassemble')
    after_build(function (target) 
        local builddir = target:targetdir()
        local elf_file = target:targetfile()
        local elf_name = target:name()
        local toolchain = target:compiler('cc'):toolchain():fullname() 

        os.runv(
            toolchain .. '-objdump',
            {'-Sd', '--visualize-jumps', elf_file}, 
            {stdout = path.join(builddir, elf_name .. '.s')}
        )
    end)

    after_clean(function (target) 
        os.rm(path.join(target:targetdir(), target:name() .. '.s'))
    end)

rule('generate.sizeinfo')
    after_build(function (target) 
        local elf_file = target:targetfile()
        local toolchain = target:compiler('cc'):toolchain():fullname() 

        os.execv(toolchain ..'-size', {elf_file})
    end)

rule('generate.extrafiles')
    add_deps(
        'generate.map',
        'generate.bin',
        'generate.disassemble',
        'generate.sizeinfo'
    )
