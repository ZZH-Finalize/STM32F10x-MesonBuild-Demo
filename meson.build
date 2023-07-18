project('demo', 'c',
    version : '0.1',
    default_options : ['warning_level=3']
)

# check cross compile
assert(meson.is_cross_build(),
    'This project must be cross compile!\n' +
    'add --cross-file= to switch to corss compile'
)

# check compile for STM32
assert(meson.get_external_property('target_mcu', '').contains('stm32f10'),
    'This project is only for STM32 F10x series\n' + 
    'Please select your MCU cross file in cross_files subdir'
)

# stm32 lib path
dir_prefix = 'STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/'

# stm32 lib include dirs
incs = [
    'CMSIS/CM3/CoreSupport',
    'CMSIS/CM3/DeviceSupport/ST/STM32F10x',
    'STM32F10x_StdPeriph_Driver/inc'
]

# peripheral drvs
stm32_mod_path = 'STM32F10x_StdPeriph_Driver/src/stm32f10x_@0@.c'
stm32_modules = {
    'adc': true, 'bkp': true, 'can': true, 'cec': true, 'crc': true,
    'dac': true, 'dbgmcu': true, 'dma': true, 'exti': true, 'flash': true,
    'fsmc': true, 'gpio': true, 'i2c': true, 'iwdg': true, 'pwr': true,
    'rcc': true, 'rtc': true, 'sdio': true, 'spi': true, 'tim': true,
    'usart': true, 'wwdg': true,
}

# other support files
stm32_std_lib_srcs = [
    'CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_md.s',
    'CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c',
    'CMSIS/CM3/CoreSupport/core_cm3.c',
    'STM32F10x_StdPeriph_Driver/src/misc.c',
]

# add enabled module files to compile list
foreach module, enable : stm32_modules
    if enable
        stm32_std_lib_srcs += stm32_mod_path.format(module)
    endif
endforeach

# applicaton src files
app_srcs = [
   'main.c'
]

srcs = app_srcs
inc_dirs = []

# append stm32 lib src files to all src list
foreach src : stm32_std_lib_srcs
    srcs += dir_prefix / src
endforeach

# append stm32 lib inc files to all include dirs
foreach inc : incs
    inc_dirs += dir_prefix / inc
endforeach

# message('srcs:', srcs)
# message('inc_dirs:', inc_dirs)

# get cross tools from cross file
objcopy_tool = find_program('objcopy')
objdump_tool = find_program('objdump')
size_tool = find_program('size')
gdb_tool = find_program('gdb')

proj_name = meson.project_name()
exe_sufix = meson.get_external_property('exe_sufix')

# c_args apply to all src files
c_args = [
    '-mcpu=' + host_machine.cpu(),
    '-DSTM32F10X_MD',
    '-DUSE_STDPERIPH_DRIVER',
    '-DPROJECT_VERSION=' + '"' + meson.project_version() + '"',
]

# link args apply to the project
link_args = [
    '-mcpu=' + host_machine.cpu(),
]

# get memory configuration from cross file
mem_cfg = {
    'flash_base': meson.get_external_property('flash_base'),
    'flash_size': meson.get_external_property('flash_size'),
    'ram_base': meson.get_external_property('ram_base'),
    'ram_size': meson.get_external_property('ram_size'),
}

# all target description
target_dict = {
    'dbg' : {
        'c_args': [
            '-D__DEBUG',
            '-DVECT_TAB_SRAM',
            '-g3',
            '-Wa,-g3'
        ],
        'link_args': ['-Wl,-Map,memory_ram.map'],
        'linker_script': 'linker_ram.ld',
        'debug': true,
    },
    'rel' : {
        'c_args': ['-O2'],
        'link_args': ['-Wl,-Map,memory.map'],
        'linker_script': 'linker.ld',
    }
}

top_objs = []
dbg_target = ''

# generate all target build setup
foreach target_name, options : target_dict
    target_srcs = srcs + options.get('srcs', [])
    exe_name = proj_name + '_@0@.@1@'.format(target_name, exe_sufix)
    lds = target_name + '_' + options['linker_script']

    configure_file(
        input: 'linker_sct' / options['linker_script'],
        output: lds,
        configuration: mem_cfg
    )

    lds = '-T' + (meson.current_build_dir() / lds)

    exe = executable(exe_name, target_srcs,
        include_directories : inc_dirs,
        c_args: c_args + options.get('c_args', []),
        link_args : link_args + lds + options.get('link_args', [])
    )

    dis = custom_target(target_name + '_dis',
        depends: exe,
        capture: true,
        command: [
            objdump_tool.full_path(),
            '-SD',
            meson.current_build_dir() / exe.name()
        ],
        output: [exe.name().split('.')[0] + '.s']
    )

    size = run_target(target_name + '_size',
        depends: dis,
        command: [
            size_tool.full_path(),
            meson.current_build_dir() / exe.name(),
        ]
    )

    top_objs += dis

    bin = custom_target(target_name + '_bin',
        depends: dis,
        command : [
            objcopy_tool.full_path(),
            '-O', 'binary',
            meson.current_build_dir() / exe.name(),
            meson.current_build_dir() / '@OUTPUT@'
        ],
        output: [exe.name().split('.')[0] + '.bin']
    )

    if options.get('debug', false)
        dbg_target = exe.name()
    endif

endforeach

# custom target to build all target in the 'target_dict'
run_target('top_all',
    depends: top_objs,
    command: ['echo', 'all target built done']
)

# generate vscode workspace file
cross_file = 'cross_files' / meson.get_external_property('target_mcu') + '.cfg'
configure_file(
    input: 'proj_files' / 'workspace_demo.json',
    output: proj_name + '.code-workspace',
    configuration: {
        'debug_file': dbg_target,
        'gdb_path': gdb_tool.full_path(),
        'cross_file': cross_file
    },
)

# generate download script
configure_file(
    input: 'proj_files' / 'download_demo.sh',
    output: 'download.sh',
    configuration: {
        'flash_base': mem_cfg['flash_base']
    }
)
