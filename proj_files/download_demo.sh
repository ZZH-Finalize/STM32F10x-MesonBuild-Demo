openocd -f $1 -f openocd_cfg/stm32f1x.cfg -c init -c "reset halt; wait_halt; flash write_image erase $2 @flash_base@" -c reset -c shutdown
