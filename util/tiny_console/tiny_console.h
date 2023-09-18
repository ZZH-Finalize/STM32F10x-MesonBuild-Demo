#ifndef __TINY_CONSOLE_H__
#define __TINY_CONSOLE_H__

#include <stdint.h>
#include <errno.h>
#include "tiny_console_conf.h"
#include "util/arg_checkers.h"
#include "util/gnu_attributes.h"
#include "util/mem_mana/mem_mana.h"

struct __console_t;

// return 1 value when succ
// return negative value when fail
typedef int (*console_char_out_t)(struct __console_t*, char);

typedef enum
{
    concole_color_black = '0',
    concole_color_red,
    concole_color_green,
    concole_color_yellow,
    concole_color_blue,
    concole_color_purple,
    concole_color_dark_green,
    concole_color_white,
} console_color_t;

typedef struct __console_t
{
    void* user_data;
    const char *prefix, *cwd;
    uint32_t buffer_size;
    uint32_t cursor_pos;
    int last_ret_v;

    console_char_out_t write_char;

    char buf[];
} console_t;

console_t* console_create(uint32_t buffer_size, console_char_out_t output_fn,
                          const char* prefix, void* user_data);

static inline void console_delete(console_t* this)
{
    memFree(this);
}

static inline void console_char_input(console_t* this, char ch)
{
    CHECK_PTR(this, );

    if (this->cursor_pos < this->buffer_size)
        this->buf[this->cursor_pos++] = ch;
}

int console_send_str(console_t* this, const char* str);
int console_printf(console_t* this, const char* fmt, ...) GNU_PRINTF(2, 3);

static inline int console_set_color(console_t* this, console_color_t font_color,
                             console_color_t back_color)
{
    char buf[] = {"\033[4\0;3\0m"};
    buf[6] = font_color;
    buf[3] = back_color;
    return console_send_str(this, buf);
}

static inline int console_cancel_color(console_t* this)
{
    return console_send_str(this, "\033[0m");
}

static inline void console_display_prefix(console_t* this)
{
    console_set_color(this, concole_color_green, concole_color_black);
    console_send_str(this, this->prefix);
    console_cancel_color(this);

    this->write_char(this, ':');

    console_set_color(this, concole_color_blue, concole_color_black);
    console_send_str(this, this->cwd);
    console_cancel_color(this);

    this->write_char(this, '$');
    this->write_char(this, ' ');
}

#endif  // __TINY_CONSOLE_H__
