#ifndef __RINGBUF_H__
#define __RINGBUF_H__

#include <stddef.h>
#include <stdint.h>
#include "util/arg_checkers.h"
#include "util/mem_mana/mem_mana.h"

#define RB_CHECK(cond, retv)          RETURN_IF(cond, retv)
#define RB_CHECK_POINTER(ptr, retv)   RB_CHECK(NULL == ptr, retv)
#define RB_RETURN_IF_ZERO(cond, retv) RETURN_IF_ZERO(cond, retv)

typedef struct
{
    uint32_t wpos;
    uint32_t rpos;
    uint32_t size;
    uint8_t buf[];
} ringbuf_t;

typedef struct
{
    ringbuf_t* prb;
    uint8_t lock;
} ringbuf_locked_t;

/**
 *@brief create a ringbuf on a buffer in the specific memory pool
 *
 * @param buffer - buffer address
 * @param pool - memory pool id
 * @param size - buffer size
 */
static inline ringbuf_t* ringbuf_create_in_pool(uint32_t buffer_size,
                                                uint32_t pool)
{
    RB_RETURN_IF_ZERO(buffer_size, NULL);

    ringbuf_t* this =
        (ringbuf_t*) memAlloc(sizeof(ringbuf_t) + buffer_size, pool);

    RB_CHECK_POINTER(this, NULL);

    this->size = buffer_size;
    this->rpos = 0;
    this->wpos = 0;

    return this;
}

/**
 *@brief create a ringbuf on a buffer
 *
 * @param buffer - buffer address
 * @param size - buffer size
 */
static inline ringbuf_t* ringbuf_create(uint32_t buffer_size)
{
    return ringbuf_create_in_pool(buffer_size, MEMPOOL_DEFAULT);
}

/**
 * @brief delete a ringbuf
 *
 * @param this - ringbuf_t struct
 */
static inline void ringbuf_delete(ringbuf_t* this)
{
    memFree(this);
}

/**
 * @brief clear a ring buf
 *
 * @param this - ringbuf struct pointer
 */
static inline void ringbuf_clear(ringbuf_t* this)
{
    RB_CHECK_POINTER(this, );

    this->rpos = this->wpos = 0;
}

/**
 *@brief check the given ringbuf is empty or not
 *
 * @param this - ringbuf struct pointer
 * @return uint8_t 0: not empty, 1: empty
 */
static inline uint8_t ringbuf_empty(ringbuf_t* this)
{
    RB_CHECK_POINTER(this, 0);

    return this->wpos == this->rpos;
}

/**
 * @brief check the given rinbuf is full or not
 *
 * @param this - ringbuf_t struct
 * @return uint8_t 0: not full, 1: full
 */
static inline uint8_t ringbuf_full(ringbuf_t* this)
{
    if (0 == this->rpos)
        return this->wpos == this->size - 1;
    else
        return this->wpos == this->rpos - 1;
}

/**
 *@brief get ringbuf size
 *
 * @param this - ringbuf struct pointer
 * @return uint32_t - size of ringbuf
 */
static inline uint32_t ringbuf_size(ringbuf_t* this)
{
    RB_CHECK_POINTER(this, 0);

    return this->size;
}

/**
 * @brief get writeable address
 *
 * @param this - ringbuf_t struct
 * @return void* writeable pointer
 */
static inline void* ringbuf_wpos(ringbuf_t* this)
{
    RB_CHECK_POINTER(this, NULL);
    return &this->buf[this->wpos];
}

/**
 * @brief get readable address
 *
 * @param this - ringbuf_t struct
 * @return void* readable pointer
 */
static inline void* ringbuf_rpos(ringbuf_t* this)
{
    RB_CHECK_POINTER(this, NULL);
    return &this->buf[this->rpos];
}

/**
 * @brief get the length of continuous memory that could be read
 *
 * @param this - ringbuf_t struct
 * @return uint32_t length of the continuous memory
 */
static inline uint32_t ringbuf_get_seq_read_len(ringbuf_t* this)
{
    RB_CHECK_POINTER(this, 0);
    return this->size - this->rpos;
}

/**
 * @brief get the length of continuous memory that could be write
 *
 * @param this - ringbuf_t struct
 * @return uint32_t length of the continuous memory
 */
static inline uint32_t ringbuf_get_seq_write_len(ringbuf_t* this)
{
    RB_CHECK_POINTER(this, 0);

    if (this->wpos >= this->rpos)
        return this->size - this->wpos;
    else
        return this->rpos - this->wpos;
}

// w > r
// 0 1 2  3 4 5 6 7 8  9 10 11
//[][][r][][][][][][w][][][]
// free bytes = 12-8 = 4 + 2 - 1 = 5(size-w+r-1)
// available bytes = 8-2 = 6 = (w-r)

// r > w
// 0 1 2  3 4 5 6 7 8  9 10 11
//[][][w][][][][][][r][][][]
// free bytes = 8-2-1 = 5 (r-w-1)
// available bytes = 12-8 = 4 + 2 = 6(size-r+w)

// w > r
// 0 1 2  3 4 5 6  7 8 9 10 11
//[][][r][][][][w][][][][][]
// free bytes = 12-6 = 6 + 2 - 1 = 7(size-w+r-1)
// available bytes = 6-2 = 4 = (w-r)

// r > w
// 0 1 2  3 4 5 6  7 8 9 10 11
//[][][w][][][][r][][][][][]
// free bytes = 6-2-1 = 3 (r-w-1)
// available bytes = 12-6 = 6 + 2 = 8(size-r+w)

/**
 *@brief get free space of a ringbuf (how many bytes could be write)
 *
 * @param this - ringbuf struct pointer
 * @return uint32_t free bytes
 */
static inline uint32_t ringbuf_get_free_bytes(ringbuf_t* this)
{
    RB_CHECK_POINTER(this, 0);

    if (this->wpos >= this->rpos)
        return this->size - this->wpos + this->rpos - 1;
    else
        return this->rpos - this->wpos - 1;
}

/**
 *@brief get available bytes (how many bytes could be read)
 *
 * @param this - ringbuf struct pointer
 * @return uint32_t avaliable bytes
 */
static inline uint32_t ringbuf_get_available_bytes(ringbuf_t* this)
{
    RB_CHECK_POINTER(this, 0);

    if (this->wpos >= this->rpos)
        return this->wpos - this->rpos;
    else
        return this->size - this->rpos + this->wpos;
}

/**
 *@brief increase internal write pos (may be write by dma)
 *
 * @param this - ringbuf struct pointer
 * @param num - how many bytes needs to be increase
 */
static inline void ringbuf_increase_bytes(ringbuf_t* this, uint32_t num)
{
    // RB_CHECK_POINTER(this, );
    this->wpos += num;
    this->wpos %= this->size;
}

/**
 *@brief increase internal read pos (drop some bytes, may be read by dma)
 *
 * @param this - ringbuf struct pointer
 * @param num how many bytes needs to be drop
 */
static inline void ringbuf_drop_bytes(ringbuf_t* this, uint32_t num)
{
    // RB_CHECK_POINTER(this, );
    this->rpos += num;
    this->rpos %= this->size;
}

/**
 *@brief get internal buffer pointer
 *
 * @param this - ringbuf struct pointer
 * @return void* - buffer pointer
 */
static inline void* ringbuf_get_buffer(ringbuf_t* this)
{
    RB_CHECK_POINTER(this, 0);
    return this->buf;
}

/**
 *@brief write data to ringbuf
 *
 * @param this - ringbuf struct pointer
 * @param data - data address
 * @param size - data length
 * @return uint32_t - actual write length
 */
uint32_t ringbuf_write(ringbuf_t* this, void* data, uint32_t size);

/**
 *@brief read data to ringbuf
 *
 * @param this - ringbuf struct pointer
 * @param data - data address
 * @param size - data length
 * @return uint32_t - actual read length
 */
uint32_t ringbuf_read(ringbuf_t* this, void* data, uint32_t size);

/**
 *@brief write one byte to ringbuf
 *
 * @param this - ringbuf struct pointer
 * @param byte - byte data
 */
void ringbuf_write_byte(ringbuf_t* this, uint8_t byte);

/**
 *@brief read one byte from ringbuf
 *
 * @param this - ringbuf struct pointer
 * @return uint8_t - byte data
 */
uint8_t ringbuf_read_byte(ringbuf_t* this);

/**
 *@brief find a specific byte data in ringbuf
 *
 * @param this - ringbuf struct pointer
 * @param byte - byte data
 * @return void* - data pos
 */
void* ringbuf_chb(ringbuf_t* this, uint8_t byte);

#endif // __RINGBUF_H__
