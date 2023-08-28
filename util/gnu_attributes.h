#pragma once

#define GNU_SECTION(sec) __attribute__((__section__(#sec)))
#define GNU_WEAK __attribute__((__weak__))
