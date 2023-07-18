openocd -f ../openocd_cfg/stm32f1x.cfg -f $1 -c init -c "reset halt; wait_halt; flash write_image erase $2 @flash_base@" -c reset -c shutdown
