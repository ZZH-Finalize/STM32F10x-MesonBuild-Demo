#ifndef __DELAY_H__
#define __DELAY_H__

#include <stdint.h>
#include <stddef.h>

#define NO_OPT __attribute__((optimize("O0")))

void NO_OPT delay_us_sw(uint32_t us);
void NO_OPT delay_ms_sw(uint32_t ms);

void NO_OPT delay_us_hw(uint32_t us);
void NO_OPT delay_ms_hw(uint32_t ms);

#endif // __DELAY_H__
