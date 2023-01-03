/*************************************************************************
	> File Name: common.c
	> Author: 
	> Mail: 
	> Created Time: Tue Jan  3 09:55:32 2023
 ************************************************************************/

#include "head.h"

void make_nonblock_ioctl(int fd) {
	unsigned long ul = 1;
	ioctl(fd, FIONBIO, &ul);
}

void make_block_ioctl(int fd) {
	unsigned long ul = 0;
	ioctl(fd, FIONBIO, &ul);
}

/*
这是两个函数，它们分别用于将文件描述符设置为非阻塞或阻塞模式。

make_nonblock_ioctl 函数将文件描述符设置为非阻塞模式。它使用 ioctl 函数，并将 FIONBIO 常量和一个指向 unsigned long 类型的指针传递给它。常量 FIONBIO 是用于控制文件描述符是否为阻塞或非阻塞的常量，ul 变量的值决定了文件描述符是否为阻塞模式。如果将 ul 设置为 1，则文件描述符将被设置为非阻塞模式。

make_block_ioctl 函数将文件描述符设置为阻塞模式。它的工作原理与 make_nonblock_ioctl 函数相似，只是将 ul 设置为 0。这将导致文件描述符被设置为阻塞模式。

注意：使用 ioctl 函数可能是不可移植的，因此您可能需要使用其他方法来在不同的系统上设置文件描述符的阻塞模式。
*/

void make_nonblock(int fd) {
	fcntl(fd, F_SETFL, O_NONBLOCK);
}

void make_block(int fd) {
	fcntl(fd, F_SETFL, ~O_NONBLOCK);
}