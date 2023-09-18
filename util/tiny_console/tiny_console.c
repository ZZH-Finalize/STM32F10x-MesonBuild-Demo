#include <stdio.h>
#include <stdarg.h>
#include "tiny_console.h"
#include "util/mem_mana/mem_mana.h"

console_t* console_create(uint32_t buffer_size, console_char_out_t output_fn,
                          const char* prefix, void* user_data)
{
    console_t* this =
        memAlloc(sizeof(console_t) + buffer_size, CONSOLE_MEM_POOL);

    CHECK_PTR(this, NULL);

    this->buffer_size = buffer_size;
    this->cursor_pos = 0;
    this->prefix = prefix;
    this->cwd = "~";// for now, we don't support filesystem
    this->write_char = output_fn;
    this->user_data = user_data;

    return this;
}

int console_send_str(console_t* this, const char* str)
{
    CHECK_PTR(this, -EINVAL);
    CHECK_PTR(str, -EINVAL);

    uint32_t send_len = 0;

    while ('\0' != *str) {
        int retv = this->write_char(this, *str++);
        RETURN_IF(retv < 0, retv);
        send_len++;
    }

    return send_len;
}

int console_printf(console_t* this, const char* fmt, ...)
{
    CHECK_PTR(this, 0);
    CHECK_PTR(fmt, 0);

    va_list vargs;
    va_start(vargs, fmt);

    int len = vsnprintf(this->buf, this->buffer_size, fmt, vargs);

    for (int i = 0; i < len; i++)
        this->write_char(this, this->buf[i]);

    va_end(vargs);
    return len;
}
