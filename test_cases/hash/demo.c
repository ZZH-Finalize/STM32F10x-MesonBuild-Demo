#include "hash_all_test.h"
#include "util/iterators.h"
#include "util/usart/prints.h"

static hash_func_table_t hash_funcs[] = {
    {"bkdr_hash", bkdr_hash},
    {"sdbm_hash", sdbm_hash},
    {"rs_hash",   rs_hash  },
    {"js_hash",   js_hash  },
    {"pjw_hash",  pjw_hash },
    {"elf_hash",  elf_hash },
    {"djb_hash",  djb_hash },
    {"ap_hash",   ap_hash  },
};

void str_hash_demo(void)
{
    const char* test_str = "";
    ITER_ARRAY(hash_info, hash_funcs)
    {
        usart_printf(USART1, "%s: %ld\r\n", hash_info->name,
                     hash_info->func(test_str));
    }
}
EXPORT_DEMO(str_hash_demo);
