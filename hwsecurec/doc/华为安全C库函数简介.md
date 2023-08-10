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

 

