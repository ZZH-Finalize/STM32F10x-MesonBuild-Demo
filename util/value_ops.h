#ifndef __VALUE_OPS_H__
#define __VALUE_OPS_H__

#include <stdint.h>
#include <string.h>
#include "gnu_attributes.h"

#define MAX(a, b)      ((a) > (b) ? (a) : (b))
#define MIN(a, b)      ((a) < (b) ? (a) : (b))

#define POW_OF_2(exp)  (1 << (uint32_t) (exp))

/**
 * @brief Generate a number which the lower num bits are all 1
 *
 * @param num: how many bits need to be set to 1
 * @return generated number
 */
#define FILL_BITS(num) (0 == (num) ? 0 : (POW_OF_2(num) - 1))

/**
 * @brief Generate a number which the low_bit to high_bit are all 1
 *
 * @param low_bit: lowest bit index (start from 0)
 * @param high_bit: highest bit index (start from 0)
 * @return generated number
 */
#define FILL_RANGE(low_bit, high_bit) \
    (FILL_BITS(((high_bit) + 1) - (low_bit)) << (low_bit))

#define BYTE_AT(num, index) (((num) >> ((index) * 8)) & 0xFF)

#define BIT_AT(num, index)  (((num) & (1 << (index))) != 0)

/**
 * @brief Get value inside bit index range [high_bit:low_bit]
 *
 * @param low_bit: lowest bit index (start from 0)
 * @param high_bit: highest bit index (start from 0)
 * @return value of expected bit range (closed range)
 */
#define BITS_AT(num, low_bit, high_bit) \
    (((num) >> (low_bit)) & FILL_BITS(((high_bit) + 1) - (low_bit)))

/**
 * @brief Judge a value is power of 2 or not
 *
 * @param value: value
 * @return true: value is power of 2
 * @return false: value is not power of 2
 */
#define IS_POW_OF_2(value) (((value) & ((value) -1)) == 0)

/**
 * @brief find first 1
 *
 * @return u8: first 1 index (in bit)
 */
GNU_PURE uint8_t ff1(size_t num);

/*
@brief 得到位倒序后的输入值
@param num 需要倒序的值
@param bitsOfVar 需要倒序的二进制长度
@return 倒序后的值
*/
GNU_PURE size_t reverseBits(size_t num, uint8_t bitsOfVar);

/**
 * @brief
 *
 * @param pnum: pointer to values
 * @param low_bit: low bit index (start from 0)
 * @param high_bit: high bit index (start from 0)
 * @return uint32_t: value of marked bit range (closed range)
 */
uint32_t valueAt(uint32_t *pnum, uint32_t low_bit, uint32_t high_bit);

#endif // __VALUE_OPS_H__
