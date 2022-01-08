#### 6.1
未初始化数据存放在BSS段，未分配存储空间

```bash
ls -l mem_segments
-rwxr-xr-x 1 xmchxcoder xmchxcoder 17000 Jan  8 09:20 mem_segments

size mem_segments
   text    data     bss     dec         hex     filename
   2001     636 10305568    10308205    9d4a6d  mem_segments
```

#### 6.2
see [code](./6_2.c) 

由于fun已经返回，所以fun的栈帧不再被维护，会被写入垃圾数据使程序混乱。


#### 6.3
see [code](./6_3.c)