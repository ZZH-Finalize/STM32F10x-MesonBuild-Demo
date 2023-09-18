#include "tiny_console.h"
#include "util/mem_mana/mem_mana.h"

console_t* console_create(uint32_t buffer_size, console_char_out_t output_fn,
                          const char* prefix)
{
    console_t* this =
        memAlloc(sizeof(console_t) + buffer_size, CONSOLE_MEM_POOL);

    CHECK_PTR(this, NULL);

    this->buffer_size = buffer_size;
    this->cursor_pos = 0;
    this->prefix = prefix;
    this->write_char = output_fn;

    return this;
}
