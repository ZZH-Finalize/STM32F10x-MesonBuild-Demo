#ifndef __GNU_ATTRIBUTES_H__
#define __GNU_ATTRIBUTES_H__

#define GNU_ARRT(attr)          __attribute__((attr))
#define GNU_SECTION(sec)        GNU_ARRT(__section__(#sec))
#define GNU_WEAK                GNU_ARRT(__weak__)
#define GNU_HOT                 GNU_ARRT(__hot__)
#define GNU_PURE                GNU_ARRT(__pure__)
#define GNU_FORMAT(fmt, fa, va) GNU_ARRT(__format__(fmt, fa, va))
#define GNU_PRINTF(fa, va)      GNU_FORMAT(__printf__, fa, va)
#define GNU_SCANF(fa, va)       GNU_FORMAT(__scanf__, fa, va)

#endif  // __GNU_ATTRIBUTES_H__
