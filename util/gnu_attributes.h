#ifndef __GNU_ATTRIBUTES_H__
#define __GNU_ATTRIBUTES_H__

#define GNU_SECTION(sec) __attribute__((__section__(#sec)))
#define GNU_WEAK         __attribute__((__weak__))
#define GNU_HOT          __attribute__((__hot__))
#define GNU_PURE         __attribute__((__pure__))

#endif // __GNU_ATTRIBUTES_H__
