# 华为安全C库函数简介

## memcpy_s

函数原型：

```c
errno_t memcpy_s(void *dest, size_t destMax, const void *src, size_t count)
```

参数：

- dest：目标缓冲区地址
- destMax：目标缓冲区最大容量（以字节为单位）
- src：进行复制操作的缓冲区
- count：要复制的字符数

返回值：

- 成功返回0，失败返回错误码

示例：

```c
#include "rtthread.h"

#define SECUREC_ENABLE_MEMCPY 1
#include "securec.h"

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

```



## wmemcpy_s
## memmove_s
## wmemmove_s
## memset_s
## strcpy_s
## wcscpy_s
## strncpy_s
## wcsncpy_s
## strcat_s
## wcscat_s
## strncat_s
## wcsncat_s
## strtok_s
## cwcstok_s
## sprintf_s
## swprintf_s
## vsprintf_s
## vswprintf_s
## snprintf_s
## vsnprintf_s
## scanf_s
## wscanf_s
## vscanf_s
## vwscanf_s
## fscanf_s
## fwscanf_s
## vfscanf_s
## vfwscanf_s
## sscanf_s
## swscanf_s
## vsscanf_s
## vswscanf_s
## gets_s

 

