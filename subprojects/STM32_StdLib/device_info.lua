devices = {
    'STM32F103T4',
    'STM32F103C4',
    'STM32F103R4',
    'STM32F103T6',
    'STM32F103C6',
    'STM32F103R6',
    'STM32F103T8',
    'STM32F103C8',
    'STM32F103R8',
    'STM32F103V8',
    'STM32F103TB',
    'STM32F103CB',
    'STM32F103RB',
    'STM32F103VB',
    'STM32F103RC',
    'STM32F103VC',
    'STM32F103ZC',
    'STM32F103RD',
    'STM32F103VD',
    'STM32F103ZD',
    'STM32F103RE',
    'STM32F103VE',
    'STM32F103ZE',
    'STM32F103RF',
    'STM32F103VF',
    'STM32F103ZF',
    'STM32F103RG',
    'STM32F103VG',
    'STM32F103ZG',
}

local capacity_info = {
    'LD', 'LD_VL', 'MD', 'MD_VL', 'HD', 'HD_VL', 'XL', 'CL'
}

local memory_info = {
    {
        capacity = 'LD',
        ram_size = '6K',
        flash_size = '16K',
    },
    {
        capacity = 'LD',
        ram_size = '10K',
        flash_size = '32K',
    },
    {
        capacity = 'MD',
        ram_size = '20K',
        flash_size = '64K',
    },
    {
        capacity = 'MD',
        ram_size = '20K',
        flash_size = '128K',
    },
    {
        capacity = 'HD',
        ram_size = '48K',
        flash_size = '256K',
    },
    {
        capacity = 'HD',
        ram_size = '64K',
        flash_size = '384K',
    },
    {
        capacity = 'HD',
        ram_size = '64K',
        flash_size = '512K',
    },
    {
        capacity = 'XL',
        ram_size = '96K',
        flash_size = '768K',
    },
    {
        capacity = 'XL',
        ram_size = '96K',
        flash_size = '1M',
    },
}

device_table = {
    -- 6K/16K
    STM32F103T4 = {
        memory = memory_info[1],
    },
    STM32F103C4 = {
        memory = memory_info[1],
    },
    STM32F103R4 = {
        memory = memory_info[1],
    },

    -- 10K/32K
    STM32F103T6 = {
        memory = memory_info[2],
    },
    STM32F103C6 = {
        memory = memory_info[2],
    },
    STM32F103R6 = {
        memory = memory_info[2],
    },

    -- 20K/64K
    STM32F103T8 = {
        memory = memory_info[3],
    },
    STM32F103C8 = {
        memory = memory_info[3],
    },
    STM32F103R8 = {
        memory = memory_info[3],
    },
    STM32F103V8 = {
        memory = memory_info[3],
    },

    -- 20K/128K
    STM32F103TB = {
        memory = memory_info[4],
    },
    STM32F103CB = {
        memory = memory_info[4],
    },
    STM32F103RB = {
        memory = memory_info[4],
    },
    STM32F103VB = {
        memory = memory_info[4],
    },

    -- 48K/256K
    STM32F103RC = {
        memory = memory_info[5],
    },
    STM32F103VC = {
        memory = memory_info[5],
    },
    STM32F103ZC = {
        memory = memory_info[5],
    },

    -- 64K/384K
    STM32F103RD = {
        memory = memory_info[6],
    },
    STM32F103VD = {
        memory = memory_info[6],
    },
    STM32F103ZD = {
        memory = memory_info[6],
    },

    -- 64K/512K
    STM32F103RE = {
        memory = memory_info[7],
    },
    STM32F103VE = {
        memory = memory_info[7],
    },
    STM32F103ZE = {
        memory = memory_info[7],
    },

    -- 96K/768K
    STM32F103RF = {
        memory = memory_info[8],
    },
    STM32F103VF = {
        memory = memory_info[8],
    },
    STM32F103ZF = {
        memory = memory_info[8],
    },

    -- 96K/1M
    STM32F103RG = {
        memory = memory_info[9],
    },
    STM32F103VG = {
        memory = memory_info[9],
    },
    STM32F103ZG = {
        memory = memory_info[9],
    },
}
