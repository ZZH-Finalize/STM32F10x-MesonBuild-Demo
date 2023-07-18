# STM32F10x Meson Build Demo Project

This project is a demo for meson users to cross build STM32 projects.

To use this demo as your project template, you could follow the following steps:

1. clone this project with --depth=1 argument
2. delete .git directory
3. run command "meson setup builddir --cross-file cross_files/stm32f10x.ini --cross-file cross_files/[specific_stm32_model.ini]"
4. copy builddir/demo.code-workspace file to parent directory
5. double click demo.code-workspace then vscode will open a workspace
6. run "meson - build" vscode task (hotkey: ctrl+shift+b)
7. press F5 to launch openocd to debug

If you need to download your code to chip flash memory, then:

1. open "meson" tabbar and unfold "Targets"
2. click download, then meson will build a binary file and use openocd to download it
