#ifndef __TINY_CONSOLE_H__
#define __TINY_CONSOLE_H__

#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "tiny_console_conf.h"
#include "util/arg_checkers.h"
#include "util/gnu_attributes.h"
#include "util/mem_mana/mem_mana.h"
#include "util/map/map.h"

struct __console_t;

// return positive value when succ
// return negative value when fail
typedef int (*console_out_t)(struct __console_t*, const char*, uint32_t);

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

typedef enum
{
    console_state_normal,
    console_state_033,
} console_state_t;

typedef struct __console_t
{
    const char *prefix, *cwd;
    uint32_t buffer_size;
    uint32_t mem_pool;
    console_state_t current_state;
    int last_ret_v;

    console_out_t write;
    map_t* command_table;
    char *rxbuf, *txbuf;
    uint32_t rx_idx, tx_idx;
    uint32_t last_rx_idx;
} console_t;

int console_init(console_t* this, uint32_t buffer_size, console_out_t output_fn,
                 const char* prefix);

console_t* console_create_in_pool(uint32_t buffer_size, console_out_t output_fn,
                                  const char* prefix, uint32_t pool);

static inline console_t* console_create(uint32_t buffer_size,
                                        console_out_t output_fn,
                                        const char* prefix)
{
    return console_create_in_pool(buffer_size, output_fn, prefix,
                                  MEMPOOL_DEFAULT);
}

static inline void console_delete(console_t* this)
{
    map_delete(this->command_table);
    memFree(this->txbuf);
    memFree(this->rxbuf);
    memFree(this);
}

static inline int console_flush(console_t* this)
{
    CHECK_PTR(this, -EINVAL);
    RETURN_IF_ZERO(this->tx_idx, 0);

    uint32_t tx_idx = this->tx_idx;
    this->tx_idx = 0;
    return this->write(this, this->txbuf, tx_idx);
}

int console_send_str(console_t* this, const char* str);
int console_send_char(console_t* this, const char ch);
int console_printf(console_t* this, const char* fmt, ...) GNU_PRINTF(2, 3);

#define console_send_strln(this, str) console_send_str(this, str "\r\n")
#define console_println(this, fmt, ...) \
    console_printf(this, fmt "\r\n", ##__VA_ARGS__)

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

void console_display_prefix(console_t* this);

typedef union
{
    const void* vp;
    const uint32_t unum;
    const int32_t num;
    const float fnum;
    const char* str;
} console_cmd_arg_t;

// return 0 when succ
// return negative value when fail
typedef int (*console_cmdfn_t)(console_t* this, const int argc,
                               const console_cmd_arg_t* argv);

typedef struct
{
    const char* cmd;
    const char* desc;
    const char* arg_desc;
    console_cmdfn_t fn;
} console_cmd_desc_t;

static inline int console_register_command(console_t* this,
                                           console_cmd_desc_t* desc)
{
    CHECK_PTR(this, -EINVAL);
    CHECK_PTR(desc, -EINVAL);

    return map_insert(this->command_table, desc->cmd, (size_t) desc);
}

static inline int console_unregister_command(console_t* this, const char* cmd)
{
    CHECK_PTR(this, -EINVAL);
    CHECK_PTR(cmd, -EINVAL);

    return map_remove(this->command_table, cmd);
}

void console_update(console_t* this);

static inline int console_input(console_t* this, char* data, uint32_t len)
{
    CHECK_PTR(this, -EINVAL);
    CHECK_PTR(this->rxbuf, -EINVAL);
    RETURN_IF(this->rx_idx >= this->buffer_size, -ENOBUFS);

    for (uint32_t i = 0; i < len; i++) {
        this->rxbuf[this->rx_idx] = *data;
        this->rx_idx++;
        data++;
    }

    return 0;
}

static inline int console_input_char(console_t* this, char data)
{
    CHECK_PTR(this, -EINVAL);
    CHECK_PTR(this->rxbuf, -EINVAL);
    RETURN_IF(this->rx_idx >= this->buffer_size, -ENOBUFS);

    this->rxbuf[this->rx_idx] = data;
    this->rx_idx++;

    return 0;
}

#endif // __TINY_CONSOLE_H__
