#ifndef __TINY_CONSOLE_H__
#define __TINY_CONSOLE_H__

#include <stdint.h>
#include "util/arg_checkers.h"

typedef struct
{
    char* buf;
    uint32_t buffer_size;
    uint32_t cursor_pos;
    const char* prefix;

} console_t;

static inline void console_char_input(console_t* this, char ch)
{
    CHECK_PTR(this, );
    CHECK_PTR(this->buf, );

    if(this->cursor_pos < this->buffer_size)
        this->buf[this->cursor_pos++] = ch;
}

#endif // __TINY_CONSOLE_H__
