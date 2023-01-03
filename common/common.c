/*************************************************************************
	> File Name: common.c
	> Author: 
	> Mail: 
	> Created Time: Tue Jan  3 09:55:32 2023
 ************************************************************************/

#include "head.h"

char *get_value(char *path, char *key) {
	FILE *fp = NULL;
	// man getline
	ssize_t nrd;
	char *line = NULL;
	size_t linecap;

	char *sub = NULL;// where the '=' in 
	//char *ans = NULL;// ip address
	extern char ans[50];
	if (path == NULL || key == NULL) {
		fprintf(stderr, "Error in argument!\n");
		return NULL;
	}
	if ((fp = fopen(path, "r")) == NULL) {// open file
		perror("fopen");
		return NULL;
	}
	while ((nrd = getline(&line, &linecap, fp)) != -1) {
		if ((sub = strstr(line, key)) == NULL) {// strstr :find a string in a line
			continue;
		} else {
			if (line[strlen(key)] == '=') { // find "server = 39.96.xxx.xxx"
				strncpy(ans, sub + strlen(key) + 1, nrd - strlen(key) - 1);// put 39.96.xxxxxx into a string 
				*(ans + nrd - strlen(key) - 1) = '\0'; //set the last char to '\0'	: strcat?
			}
		}
	}
	free(line);
	fclose(fp);
	if (sub == NULL) {
		return NULL;
	}
	return ans;
}

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
	int flag;
	if ((flag = fcntl(fd, F_GETFL)) < 0) {
		return ; 
	}
	flag |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flag);
}

/*
这是一个函数，用于将文件描述符设置为非阻塞模式。

函数首先使用 fcntl 函数的 F_GETFL 选项来获取文件描述符的当前标志。如果调用失败，则函数返回。

然后，它将 flag 变量与 O_NONBLOCK 常量进行按位或运算。O_NONBLOCK 常量是用于设置文件描述符为非阻塞模式的常量。按位或运算将 flag 变量的 O_NONBLOCK 位设置为 1。

最后，函数使用 fcntl 函数的 F_SETFL 选项将修改后的 flag 值写回文件描述符。这将导致文件描述符被设置为非阻塞模式。

注意：使用 fcntl 函数可能是不可移植的，因此您可能需要使用其他方法来在不同的系统上设置文件描述符的阻塞模式。

*/

void make_block(int fd) {
	int flag;
	if ((flag = fcntl(fd, F_GETFL)) < 0) {
		return ;
	}
	flag &= ~O_NONBLOCK;
	fcntl(fd, F_SETFL, flag);
}
/*
这是一个函数，用于将文件描述符设置为阻塞模式。

函数首先使用 fcntl 函数的 F_GETFL 选项来获取文件描述符的当前标志。如果调用失败，则函数返回。

然后，它将 flag 变量与 ~O_NONBLOCK 常量进行按位与运算。O_NONBLOCK 常量是用于设置文件描述符为非阻塞模式的常量。 ~O_NONBLOCK 将 O_NONBLOCK 常量的每个位取反，然后与 flag 变量进行按位与运算。这将导致 flag 变量的 O_NONBLOCK 位被设置为 0。

最后，函数使用 fcntl 函数的 F_SETFL 选项将修改后的 flag 值写回文件描述符。这将导致文件描述符被设置为阻塞模式。

注意：使用 fcntl 函数可能是不可移植的，因此您可能需要使用其他方法来在不同的系统上设置文件描述符的阻塞模式。
*/