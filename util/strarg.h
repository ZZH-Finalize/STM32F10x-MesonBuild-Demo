#ifndef __STRARG_H__
#define __STRARG_H__

#include <stdint.h>
#include <string.h>

#define IsInCloseRange(x, d, u) (x >= d && x <= u)
#define IsInOpenRange(x, d, u)  (x > d && x < u)

#define IsLower(x)              IsInCloseRange(x, 'a', 'f')
#define IsUpper(x)              IsInCloseRange(x, 'A', 'F')
// #define IsNum(x) IsInCloseRange(x, '0', '9')
// #define IsBin(x) IsInCloseRange(x, '0', '1')
// #define IsHex(x) (IsUpper(x) || IsLower(x) || IsNum(x))

#define swap(a, b)       \
    do {                 \
        typeof(a) c = a; \
        a = b;           \
        b = c;           \
    } while (0)

uint8_t __attribute__((hot)) IsNum(char ch);

uint8_t __attribute__((hot)) IsBin(char ch);

uint8_t __attribute__((hot)) IsHex(char ch);

/*
@brief 校验一个数是否合法(二进制,十进制,十六进制)
@param str 待校验的字符串
@return 校验结果 0-非法 1-二进制 2-十进制 3-十六进制
*/
uint8_t IsVaildNum(const char* str);

/*
@brief 将字符串转为整数,自动识别格式(二进制,十进制,十六进制)
@param str 待转换的字符串
@param pNum 转换输出
@return 转换结果 0-转换失败 1-转换成功
*/
uint8_t getNum(const char* str, uint32_t* const pNum);

#endif  // __STRARG_H__
