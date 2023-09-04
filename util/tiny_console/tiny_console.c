#include "tiny_console.h"
#include "util/mem_mana/mem_mana.h"

int console_init(console_t* this, uint32_t buffer_size,
                 console_char_out_t output_fn, const char* prefix,
                 void* user_data)
{
    CHECK_PTR(this, -EINVAL);

    void* buffer = memAlloc(buffer_size, CONSOLE_MEM_POOL);
    int retv = console_init_static(this, buffer, buffer_size, output_fn, prefix,
                                   user_data);

    if (retv < 0) {
        memFree(buffer);
        return retv;
    }

    return 0;
}

int console_init_static(console_t* this, void* buffer, uint32_t buffer_size,
                        console_char_out_t output_fn, const char* prefix,
                        void* user_data)
{
    CHECK_PTR(this, -EINVAL);
    CHECK_PTR(buffer, -EINVAL);

    this->buf = buffer;
    this->buffer_size = buffer_size;
    this->cursor_pos = 0;
    this->prefix = prefix;
    this->write_char = output_fn;
    this->user_data = user_data;

    return 0;
}

console_t* console_create(uint32_t buffer_size, console_char_out_t output_fn,
                          const char* prefix, void* user_data)
{
    console_t* console = memAlloc(buffer_size, CONSOLE_MEM_POOL);

    if (console_init(console, buffer_size, output_fn, prefix, user_data) < 0) {
        memFree(console);
        console = NULL;
    }

    return console;
}

void console_deinit(console_t* this)
{
    CHECK_PTR(this, );
    memFree(this->buf);
}

void console_delete(console_t* this)
{
    console_deinit(this);
    memFree(this);
}
