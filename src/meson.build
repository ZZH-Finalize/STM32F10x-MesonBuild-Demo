find_res = run_command(ls_tool,
    '.', '-f', '^.*\.[cs]$',
    check: true,
    capture: true
)
find_srcs = find_res.stdout().splitlines()

dep = declare_dependency(
    sources: files(find_srcs),
    include_directories: include_directories(['hal', 'app'])
)

project_ss.add(dep)
