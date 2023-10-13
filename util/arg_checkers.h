#ifndef __ARG_CHECKERS_H__
#define __ARG_CHECKERS_H__

#include <stddef.h>
#include <errno.h>

// clang-format off
#define RETURN_IF(cond, retv) if (cond) return retv
#define GOTO_IF(cond, labal) if(cond) goto labal
// clang-format on

#define RETURN_IF_VALUE(cond, val, retv)  RETURN_IF((val) == (cond), retv)
#define RETURN_IF_NVALUE(cond, val, retv) RETURN_IF((val) != (cond), retv)
#define RETURN_IF_ZERO(cond, retv)        RETURN_IF_VALUE(cond, 0, retv)
#define RETURN_IF_NZERO(cond, retv)       RETURN_IF_NVALUE(cond, 0, retv)
#define CHECK_PTR(ptr, retv)              RETURN_IF(NULL == (ptr), retv)
#define CHECK_PTR_GOTO(ptr, labal)        GOTO_IF(NULL == (ptr), labal)

#define CHECK_IN_OPEN_RANGE(val, left, right, retv) \
    RETURN_IF((val) < (right) && (val) > (left), retv)

#define CHECK_IN_CLOSED_RANGE(val, left, right, retv) \
    RETURN_IF((val) <= (right) && (val) >= (left), retv)

#endif  // __ARG_CHECKERS_H__
