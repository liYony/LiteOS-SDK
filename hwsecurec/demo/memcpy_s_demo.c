#include <rtthread.h>

#define SECUREC_ENABLE_MEMCPY 1
#include <securec.h>

int memcpy_s_demo()
{
    int a1[10], a2[100], i;
    errno_t err;

    // Populate a2 with squares of integers
    for (i = 0; i < 100; i++)
    {
        a2[i] = i*i;
    }

    // Tell memcpy_s to copy 10 ints (40 bytes), giving
    // the size of the a1 array (also 40 bytes).
    err = memcpy_s(a1, sizeof(a1), a2, 10 * sizeof (int) );
    if (err)
    {
        rt_kprintf("Error executing memcpy_s.\n");
    }
    else
    {
        for (i = 0; i < 10; i++)
            rt_kprintf("%d ", a1[i]);
    }
    rt_kprintf("\n");
}
INIT_APP_EXPORT(memcpy_s_demo);
