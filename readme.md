# STM32F10x Meson Build Demo Project

This project is a demo for meson users to cross build STM32 projects.

Use VSCode with extensions is highly recommand.

The recommended extensions are these (unique id):

1. ms-vscode.cpptools
2. mesonbuild.mesonbuild

To use this demo as your project template, you could follow the following steps:

1. clone this project with --depth=1 argument
2. delete .git directory
3. edit cross_files/toolchain.ini to setting your toolchain path
4. run command `./configure.sh [project_name] cross_files/[specific_stm32_model.ini] crossfiles/debugger/[debugger_file.ini]`, the contents inside the "[]" are selected by your configuration.
5. double click [project_name].code-workspace then vscode will open a workspace
6. modify .config file to configure the project
7. run "meson - build" vscode task (hotkey: ctrl+shift+b)
8. press F5 to launch openocd to debug

If you need to download your code to chip flash memory, then:

1. open "meson" tabbar and unfold "Targets"
2. click download, then meson will build a binary file and use openocd to download it

Or use download script by running command `./builddir/download.sh`
