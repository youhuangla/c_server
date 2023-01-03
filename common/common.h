/*************************************************************************
	> File Name: common.h
	> Author: 
	> Mail: 
	> Created Time: Tue Jan  3 09:57:35 2023
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H
char *get_value(char *path, char *key);
void make_nonblock_ioctl(int fd);
void make_block_ioctl(int fd);
void make_nonblock(int fd);
void make_block(int fd);
#endif
