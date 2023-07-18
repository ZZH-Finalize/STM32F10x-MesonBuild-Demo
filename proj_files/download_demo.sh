openocd -f $1 -f $2 -c init -c "reset halt; wait_halt; flash write_image erase $3 @flash_base@" -c reset -c shutdown
