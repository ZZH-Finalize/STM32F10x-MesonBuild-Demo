#include "tiny_console.h"
#include "util/mem_mana/mem_mana.h"

int console_init(console_t* this, uint32_t buffer_size,
                 console_char_out_t output_fn, const char* prefix)
{
    CHECK_PTR(this, -EINVAL);

    this->buffer_size = buffer_size;
    this->cursor_pos = 0;
    this->prefix = prefix;
    this->write_char = output_fn;

    return 0;
}

console_t* console_create(uint32_t buffer_size, console_char_out_t output_fn,
                          const char* prefix)
{
    console_t* console =
        memAlloc(sizeof(console_t) + buffer_size, CONSOLE_MEM_POOL);

    if (console_init(console, buffer_size, output_fn, prefix) < 0) {
        memFree(console);
        console = NULL;
    }

    return console;
}
