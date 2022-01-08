## TLPI
> 《UNIX/LINUX 系统编程手册》笔记和解答

### 目录
- [TLPI](#tlpi)
  - [目录](#目录)
    - [环境搭建](#环境搭建)
    - [CH3系统编程概念](#ch3系统编程概念)
    - [CH4文件 I/O：通用的 I/O 模型](#ch4文件-io通用的-io-模型)
    - [CH5深入探究文件I/O](#ch5深入探究文件io)
    - [CH6进程](#ch6进程)


#### 环境搭建
安装依赖
```sh
sudo apt-get install libcap-dev libacl1-dev libselinux1-dev libseccomp-dev
```

编译源代码
```sh
wget https://man7.org/tlpi/code/download/tlpi-201025-dist.tar.gz
tar -zxvf tlpi-201025-dist.tar.gz
cd tlpi-dist/
make
```

拷贝自定义头文件至系统目录
```sh
cd lib/
sudo cp tlpi_hdr.h /usr/local/include/
sudo cp get_num.h /usr/local/include/
sudo cp error_functions.h /usr/local/include/
sudo cp ename.c.inc /usr/local/include/
```

老版本需要手动创建静态库
```sh
g++ -c get_num.c error_functions.c
ar -crv libtlpi.a get_num.o error_functions.o

sudo cp libtlpi.a /usr/local/lib
```

链接时需要带上静态库
```
g++ main.cpp -o main -ltlpi
```

#### [CH3系统编程概念](./exercises/ch3/README.md)
#### [CH4文件 I/O：通用的 I/O 模型](./exercises/ch4/)
#### [CH5深入探究文件I/O](./exercises/ch5/README.md)
#### [CH6进程](./exercises/ch6/README.md)