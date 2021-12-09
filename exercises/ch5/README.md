``5.1``

编译时加 ``-D_FILE_OFFSET_BITS=64`` 或者程序中定义宏``#define _FILE_OFFSET_BITS 64`` 

所有32版本位函数自动转换为64位版本, 如open() -> open64(), off_t -> off64_t


``5.2``

append总是在结尾写

``5.3``

![image](https://cdn.jsdelivr.net/gh/XmchxUp/cloudimg@master/20211209/image.15rk7oj0gcio.png)

使用append是原子的操作(lseek 和 write)

``5.6``

Hello,

Hello,world

HELLO,world

Giddayworld