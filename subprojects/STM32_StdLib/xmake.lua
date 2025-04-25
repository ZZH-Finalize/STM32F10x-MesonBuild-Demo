-- project
set_project('STM32_StdLib')
set_version('3.5.0')

includes('device_info.lua')

-- includes
add_includedirs(
    'CMSIS/CoreSupport',
    'CMSIS/DeviceSupport',
    'Driver/inc',
    {public = true}
)

-- targets
target('STM32_StdLib')
    set_kind('static')
    add_defines('USE_STDPERIPH_DRIVER', {public = true})
    add_options('target_mcu')

    -- add source files
    add_files('**.c')

-- MCU configurations
option('target_mcu')
    set_default('STM32F103C8')
    set_values(devices)
    -- local dev_info = device_table[get_config('target_mcu')]

    -- if dev_info then
    --     set_configvar('flash_size', dev_info.memory.flash_size)
    --     set_configvar('ram_size', dev_info.memory.ram_size)
    --     add_defines('STM32F10X_' .. dev_info.memory.capacity)
    -- end
    
