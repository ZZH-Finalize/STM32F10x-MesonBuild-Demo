project('demo', 'c',
    version: '0.1',
    license: 'GPL-3.0',
    license_files: 'LICENSE',
    default_options: {
        'warning_level': '3',
        'c_std': 'gnu17',
    }
)

# Check cross compile
assert(meson.is_cross_build(),
    'This project must be cross compile!\n' +
    'add --cross-file= to switch to corss compile'
)

# Check compile for STM32
target_mcu = meson.get_external_property('target_mcu', 'null')
assert(target_mcu.contains('stm32f10'),
    'This project is only for STM32 F10x series(your selection: @0@)\n'.format(target_mcu) + 
    'Please select your MCU cross file in cross_files subdir'
)

# Check specific device info
capacity = meson.get_external_property('capacity', 'null')
allowed_capacity_list = ['LD', 'LD_VL', 'MD', 'MD_VL', 'HD', 'HD_VL', 'XL', 'CL']
if false == allowed_capacity_list.contains(capacity)
    error('Unsupport capacity (your selection: @0@)\r\n'.format(capacity),
            'supported capacities are: ', allowed_capacity_list)
endif

# Project informations
proj_name = meson.project_name()
src_dir = meson.current_source_dir()
build_dir = meson.current_build_dir()
exe_sufix = meson.get_external_property('exe_sufix', 'elf')

# Get cross tools from cross file
objcopy_tool = find_program('objcopy')
objdump_tool = find_program('objdump')
size_tool = find_program('size')
gdb_tool = find_program('gdb')
ls_tool = find_program(
    'list_files.py',
    dirs: [src_dir / 'tools'],
    required: true
)

# Import modules
fs = import('fs')
ssmod = import('sourceset')

# Global informations
project_ss = ssmod.source_set()
global_config = {}

global_c_flags = [
    '-mcpu=' + host_machine.cpu(),
    '-DSTM32F10X_' + capacity,
    '-DUSE_STDPERIPH_DRIVER',
    '-DPROJECT_VERSION=' + '"' + meson.project_version() + '"',
    '-fdata-sections',
    '-ffunction-sections',
]

global_link_flags = [
    '-mcpu=' + host_machine.cpu(),
    '-nostartfiles',
    '-Wl,--gc-sections',
    '-lm',
]

# Read .config and generate marcos
if fs.exists('.config')

    config_lines = fs.read('.config')

    foreach line: config_lines.splitlines()
        if line.contains('=') and not line.startswith('#')
            line = line.strip()

            part = line.split('=')
            global_config += {part[0]: part[1]}
            global_c_flags += '-DCONFIG_' + line

        endif

    endforeach

endif

# Add all flags, srcs, incs to meson
add_global_arguments(global_c_flags, language: 'c')
add_global_link_arguments(global_link_flags, language: 'c')

# toolchain_path = fs.parent(fs.parent(find_program('c').full_path()))
# toolchain_inc = toolchain_path / 'arm-none-eabi/include'
# message(toolchain_inc)
# project_ss.add(declare_dependency(include_directories: toolchain_inc))

# Process subdirs and subprojects
subdir('src')

embed_utils_lib = subproject('embed-utils',
    default_options: {
        'buildtype': 'release',
        'default_library': 'static',
        'warning_level': '0',
    },
    required: true
)
util_dep = embed_utils_lib.get_variable('embed_utils_dep')
project_ss.add(util_dep)

stm32_lib = subproject('STM32_StdLib',
    default_options: {
        'buildtype': 'release',
        'default_library': 'static',
        'warning_level': '0',
    },
    required: true
)
stm32_dep = stm32_lib.get_variable('stm32_stdlib_dep')
project_ss.add(stm32_dep)

# Get memory configuration from cross file
mem_cfg = {
    'flash_base': meson.get_external_property('flash_base'),
    'flash_size': meson.get_external_property('flash_size'),
    'ram_base': meson.get_external_property('ram_base'),
    'ram_size': meson.get_external_property('ram_size'),
    'stack_size': meson.get_external_property('stack_size', 0x400),
}

# all target description
target_dict = {
    'dbg': {
        'c_args': [
            '-Og',
            '-DVECT_TAB_SRAM',
            '-g3',
        ],
        'link_args': [
            '--specs=nano.specs'
        ],
        'linker_script': 'linker_ram_new.ld',
        'debug': true,
    },
    'rel': {
        'c_args': ['-O2'],
        'link_args': [
            '--specs=nano.specs'
        ],
        'linker_script': 'linker_new.ld',
        'download': true,
    }
}

top_objs = []
dbg_target = ''
dl_target = ''

# generate all target build setup
foreach target_name, options : target_dict

    # Specify target informations
    exe_name = proj_name + '_@0@'.format(target_name)
    lds_name = target_name + '_' + options['linker_script']
    target_c_args = options.get('c_args', [])
    target_link_args = options.get('link_args', [])

    # Handle configs
    target_configs = global_config + options.get('configs', {})

    # Handle source set
    target_src_set = ssmod.source_set()
    target_src_set.add_all(project_ss)
    target_src_set.add(files(options.get('srcs', [])))
    target_srcs = target_src_set.apply(target_configs)

    # Handle debug flags
    if options.get('debug', false)
        target_c_args += '-D__DEBUG'
    endif

    # Handle map file and linker script
    target_link_args += '-Wl,-Map,memory_@0@.map'.format(target_name)
    target_link_args += '-T' + (build_dir / lds_name)

    lds = configure_file(
        input: 'linker_sct' / options['linker_script'],
        output: lds_name,
        configuration: mem_cfg
    )

    exe = executable(
        exe_name,
        name_suffix: exe_sufix,
        link_depends: lds,
        sources: target_srcs.sources(),
        dependencies: target_srcs.dependencies(),
        c_args: target_c_args,
        link_args: target_link_args
    )

    dis = custom_target(
        target_name + '_dis',
        depends: exe,
        capture: true,
        command: [
            objdump_tool.full_path(),
            '-SD',
            exe.full_path()
        ],
        output: fs.replace_suffix(exe.name(), '.s')
    )

    run_target(
        target_name + '_size',
        depends: dis,
        command: [
            size_tool.full_path(),
            exe.full_path(),
        ]
    )

    top_objs += dis

    bin = custom_target(
        target_name + '_bin',
        depends: dis,
        command: [
            objcopy_tool.full_path(),
            '-O', 'binary',
            exe.full_path(),
            build_dir / '@OUTPUT@'
        ],
        output: fs.replace_suffix(exe.name(), '.bin')
    )

    if options.get('debug', false)
        dbg_target = exe
    endif

    if options.get('download', false)
        dl_target = bin
    endif

endforeach

# custom target to build all target in the 'target_dict'
run_target(
    'top_all',
    depends: top_objs,
    command: ['echo', 'all target built done']
)

# generate vscode workspace file
cross_file = 'cross_files' / target_mcu + '.ini'
dfp_file = meson.get_external_property('dfp_file')
device_name = meson.get_external_property('device_name')
debugger_file = meson.get_external_property('debugger_file')
configure_file(
    input: 'proj_files' / 'workspace_demo.json',
    output: proj_name + '.code-workspace',
    configuration: {
        'debug_file': dbg_target.name(),
        'gdb_path': gdb_tool.full_path(),
        'cross_file': cross_file,
        'dfp_file': dfp_file,
        'device_name': device_name,
        'debugger_file': debugger_file,
        'debugger_file_ini': fs.replace_suffix(debugger_file, '.ini'),
        'toolchain_path': find_program('c').full_path(),
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

# download target
dl_cmd = 'flash write_image erase '
dl_cmd += dl_target.full_path() + ' '
dl_cmd += mem_cfg['flash_base'] + ' '

supported_tools = {
    'stlink': 'stlink.cfg',
    'dap': 'cmsis-dap.cfg'
}

foreach tool, cfg : supported_tools
    run_target(
        tool + ' - download',
        depends: dl_target,
        command: [
            'openocd',
            '-f', '..' / 'openocd_cfg' / cfg,
            '-f', '..' / 'openocd_cfg' / 'stm32f1x.cfg',
            '-c init;reset halt;wait_halt;',
            '-c', dl_cmd,
            '-c reset; shutdown;'
        ]
    )
endforeach
