/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Sun Jan  1 20:18:42 2023
 ************************************************************************/

#include "../common/head.h"
#include "../common/tcp_server.h"
#include "../common/common.h"

#define MAX_CLIENT 512

char *conf = "./server.conf";

int main(int argc, char **argv) {
	int port;
	port = atoi(get_value(conf, "SERVER_PORT"));
	printf("%d\n", port);
	return 0;
}
