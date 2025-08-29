#ifndef __ASYNC_H__
#define __ASYNC_H__

#include <stdint.h>
#include "linked_list/linked_list.h"

typedef struct
{
    uint32_t R[16];

    uint32_t PC;
    uint32_t SP;
    uint32_t PSR;

    list_node_t node;
} cpu_context_t;

extern void async_start_task(void);
extern void async_switch_context(void);

void trigger_svc();

void async_delay(uint32_t ms);
void async_start_schedule(void);

#endif // __ASYNC_H__
