#ifndef __MEM_CONF_H__
#define __MEM_CONF_H__

#define DEFAULT_POOL_SIZE 4  // 4K bytes

#if CONFIG_ENABLE_TEST_CASES == 1
#define TESTCASE_POOL_SIZE 1  // 1K bytes
#endif

#endif  // __MEM_CONF_H__
