/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Sun Jan  1 20:31:54 2023
 ************************************************************************/

#include "head.h"
#include "tcp_client.h"
#include <stdio.h>

int main(int argc, char **argv) {
	int sockfd;
	if (argc != 3) {
		fprintf(stderr, "Usage: %s ip port!\n", argv[0]);
		return 1;
	}
	if ((sockfd = socket_connect(argv[1], atoi(argv[2]))) < 0) {
		perror("socket_connect");
		return 2;
	}
	return 0;
}
