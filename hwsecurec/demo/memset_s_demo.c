#include <rtthread.h>

#define SECUREC_ENABLE_MEMSET 1
#include <securec.h>

int memset_s_demo()
{
    char str[] = "ssssssssssssssssssssssssssssss";

    rt_kprintf("raw str = \"%s\"\n", str);

    int r = memset_s(str, sizeof(str), 'b', 5);
    rt_kprintf("str = \"%s\", error code = %d\n", str, r);
    r = memset_s(str, 5, 'c', 10);
    rt_kprintf("str = \"%s\", error code = %d\n", str, r);
    
    return 0;
}

INIT_APP_EXPORT(memset_s_demo);
