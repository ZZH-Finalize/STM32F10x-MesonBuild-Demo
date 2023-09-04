#include "strarg.h"

/*
@brief 寻找数字里第一个为1的二进制位
@param num 需要处理的数字
@return 找到的下标 -1代表没找到
*/
__attribute__((pure)) uint8_t ff1(size_t num)
{
    if (0 == num)
        return 0;

    uint8_t bitsOfVar = sizeof(num) * 8;//通过sizeof实现自适应
    uint8_t index = 1;

    //这里执行的时候变量的位数已经固定了, 所以实际上是O(1), 32位固定循环5次, 64位固定循环6次
    while (bitsOfVar)
    {
        bitsOfVar /= 2;
        size_t tmp = num >> bitsOfVar;
        if (tmp)
        {
            index += bitsOfVar;
            num = tmp;
        }
    }

    return index;
}

/*
@brief 得到位倒序后的输入值
@param num 需要倒序的值
@param bitsOfVar 需要倒序的二进制长度
@return 倒序后的值
*/
__attribute__((pure)) size_t reverseBits(size_t num, uint8_t bitsOfVar)
{
    if (0 == num || bitsOfVar > (sizeof(num) * 8))
        return 0;

    const size_t topBit = 1 << (bitsOfVar - 1);
    bitsOfVar >>= 1;

    for (uint8_t i = 0;i < bitsOfVar;i++)
    {
        size_t lowMask = 1 << i;
        size_t highMask = topBit >> i;
        uint8_t lowBit = (num & lowMask) > 0;
        uint8_t highBit = (num & highMask) > 0;

        num &= ~(highMask | lowMask);
        num |= (highMask * lowBit) | (lowMask * highBit);
    }

    return num;
}

uint8_t __attribute__((hot)) IsNum(char ch)
{
    return IsInCloseRange(ch, '0', '9');
}

uint8_t __attribute__((hot)) IsBin(char ch)
{
    return IsInCloseRange(ch, '0', '1');
}

uint8_t __attribute__((hot)) IsHex(char ch)
{
    return IsUpper(ch) || IsLower(ch) || IsNum(ch);
}

/*
@brief 校验一个数是否合法(二进制,十进制,十六进制)
@param str 待校验的字符串
@return 校验结果 0-非法 1-二进制 2-十进制 3-十六进制
*/
uint8_t IsVaildNum(const char* str)
{
    uint8_t type = 0;

    uint8_t(*funs[])(char) = { IsBin, IsNum, IsHex };

    while (*str == '0')//跳过开头所有的0
        str++;

    if (*str == '\0')//只有0的情况下
        return 2;//算十进制0

    //根据开头定性格式
    if (*str == 'x' || *str == 'X')//十六进制
    {
        type = 2;
    }
    else if (*str == 'b' || *str == 'B')//二进制
    {
        type = 0;
    }
    else if (IsNum(*str))//十进制
    {
        type = 1;
    }
    else//非法字母
    {
        return 0;
    }

    str++;

    //校验其余字符是否合规
    while (*str != '\0')
    {
        if (!funs[type](*str++))
            return 0;
    }

    return type + 1;
}

/*
@brief 将字符串转为整数,自动识别格式(二进制,十进制,十六进制)
@param str 待转换的字符串
@param pNum 转换输出
@return 转换结果 0-转换失败 1-转换成功
*/
uint8_t getNum(const char* str, uint32_t* const pNum)
{
    if (pNum == NULL)
        return 0;

    //2-十进制 3-十六进制
    uint8_t type = IsVaildNum(str);
    *pNum = 0;

    if (type == 0)//非法字符,转换失败
    {
        return 0;
    }
    else if (type == 1)//二进制,需手动转换
    {
        str += 2;//跳过0b前缀
        while (*str != '\0')
        {
            *pNum <<= 1;
            *pNum |= *str - '0';
            str++;
        }
    }
    else if (type == 2) //十进制
    {
        while (*str != '\0')
        {
            *pNum *= 10;
            *pNum += *str - '0';
            str++;
        }
    }
    else if (type == 3) //十六进制
    {
        str += 2;//跳过0x前缀
        while (*str != '\0')
        {
            *pNum <<= 4;

            switch (*str)
            {
                case 'a' ... 'f':
                    *pNum += *str - ('a' - 10);
                    break;

                case 'A' ... 'F':
                    *pNum += *str - ('A' - 10);
                    break;

                case '0' ... '9':
                    *pNum += *str - '0';
                    break;

                default:
                    *pNum = 0;
                    return 0;
            }

            str++;
        }
    }

    return 1;
}
