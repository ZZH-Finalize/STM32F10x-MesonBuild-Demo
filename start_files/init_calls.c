#include "init_calls.h"
#include "util/iterators.h"
#include "util/linker_tools.h"

// LINKER_SYMBOL32(__sinit_func);
// LINKER_SYMBOL32(__einit_func);
LINKER_SYMBOL_TYPE(__sinit_func, __init_call_fn_t);
LINKER_SYMBOL_TYPE(__einit_func, __init_call_fn_t);

void do_init_calls(void)
{
    uint32_t init_fn_num =
        ((uint32_t)__einit_func - (uint32_t)__sinit_func) / 4;

    FOR_I(init_fn_num)
    {
        __sinit_func[i]();
    }
}
