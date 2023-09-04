#ifndef __TINY_CONSOLE_H__
#define __TINY_CONSOLE_H__

#include <stdint.h>
#include <errno.h>
#include "tiny_console_conf.h"
#include "util/arg_checkers.h"

struct __console_t;

typedef int (*console_char_out_t)(struct __console_t*, char);

typedef struct __console_t
{
    void* user_data;
    const char* prefix;
    char* buf;
    uint32_t buffer_size;
    uint32_t cursor_pos;

    console_char_out_t write_char;

} console_t;

typedef enum
{
    black = '0',
    red,
    green,
    yellow,
    blue,
    purple,
    dark_green,
    white,
} console_color_t;

static inline void console_char_input(console_t* this, char ch)
{
    CHECK_PTR(this, );
    CHECK_PTR(this->buf, );

    if (this->cursor_pos < this->buffer_size)
        this->buf[this->cursor_pos++] = ch;
}

int console_init(console_t* this, uint32_t buffer_size,
                 console_char_out_t output_fn, const char* prefix,
                 void* user_data);

int console_init_static(console_t* this, void* buffer, uint32_t buffer_size,
                        console_char_out_t output_fn, const char* prefix,
                        void* user_data);

console_t* console_create(uint32_t buffer_size, console_char_out_t output_fn,
                          const char* prefix, void* user_data);

void console_deinit(console_t* this);

void console_delete(console_t* this);

#endif  // __TINY_CONSOLE_H__
