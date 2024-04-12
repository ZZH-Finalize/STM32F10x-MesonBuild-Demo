project('STM32_StdLib', 'c',
    version: '3.5.0',
    default_options: {
        'warning_level': '3',
        'c_std': 'gnu17',
    }
)

# Project informations
proj_name = meson.project_name()
src_dir = meson.current_source_dir()
build_dir = meson.current_build_dir()

message(get_option('c_args'))

# Import modules
ssmod = import('sourceset')

# Global informations
lib_src = ssmod.source_set()
testcae_src = ssmod.source_set()
include_directories = include_directories([
    'CMSIS/CoreSupport',
    'CMSIS/DeviceSupport',
    'Driver/inc',
])

lib_src.add(declare_dependency(
    sources: files([
        'CMSIS/CoreSupport/core_cm3.c',
        'CMSIS/DeviceSupport/system_stm32f10x.c',
        'Driver/src/misc.c',
        'Driver/src/stm32f10x_adc.c',
        'Driver/src/stm32f10x_bkp.c',
        'Driver/src/stm32f10x_can.c',
        'Driver/src/stm32f10x_cec.c',
        'Driver/src/stm32f10x_crc.c',
        'Driver/src/stm32f10x_dac.c',
        'Driver/src/stm32f10x_dbgmcu.c',
        'Driver/src/stm32f10x_dma.c',
        'Driver/src/stm32f10x_exti.c',
        'Driver/src/stm32f10x_flash.c',
        'Driver/src/stm32f10x_fsmc.c',
        'Driver/src/stm32f10x_gpio.c',
        'Driver/src/stm32f10x_i2c.c',
        'Driver/src/stm32f10x_iwdg.c',
        'Driver/src/stm32f10x_pwr.c',
        'Driver/src/stm32f10x_rcc.c',
        'Driver/src/stm32f10x_rtc.c',
        'Driver/src/stm32f10x_sdio.c',
        'Driver/src/stm32f10x_spi.c',
        'Driver/src/stm32f10x_tim.c',
        'Driver/src/stm32f10x_usart.c',
        'Driver/src/stm32f10x_wwdg.c',
    ]),
    include_directories: include_directories
))

lib_src = lib_src.apply({})

lib = static_library(proj_name,
    sources: lib_src.sources(),
    dependencies: lib_src.dependencies(),
)

STM32_StdLib_dep = declare_dependency(
    link_with: lib,
    include_directories: include_directories
)


