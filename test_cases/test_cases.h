#ifndef __TEST_CASES_H__
#define __TEST_CASES_H__

#include "stm32f10x.h"
#include "test_case_conf.h"
#include "util/mem_mana/mem_pools.h"

#include "hash/hash_all_test.h"

#ifndef CONFIG_TEST_CASE_MEMPOOLS
#define CONFIG_TEST_CASE_MEMPOOLS MEMPOOL_DEFAULT
#endif  // CONFIG_TEST_CASE_MEMPOOLS


#endif  // __TEST_CASES_H__
