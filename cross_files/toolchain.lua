local tool_chain_prefix = 'arm-none-eabi'

toolchain(tool_chain_prefix)
    set_kind('standalone')

    set_toolset('cc', tool_chain_prefix .. '-gcc')
    set_toolset('cxx', tool_chain_prefix .. '-g++')
    set_toolset('ld', tool_chain_prefix .. '-gcc')
    -- set_toolset('sh', tool_chain_prefix .. '-gcc', tool_chain_prefix .. '-g++')
    set_toolset('ar', tool_chain_prefix .. '-ar')
    set_toolset('strip', tool_chain_prefix .. '-strip')
    set_toolset('as', tool_chain_prefix .. '-gcc')
    set_toolset('size', tool_chain_prefix .. '-size')
    set_toolset('objcopy', tool_chain_prefix .. '-objcopy')
    set_toolset('objdump', tool_chain_prefix .. '-objdump')
