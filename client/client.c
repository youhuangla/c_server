/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Sun Jan  1 20:31:54 2023
 ************************************************************************/

#include "../common/chatroom.h"
#include "../common/tcp_client.h"
#include "../common/common.h"

char *conf = "./client.conf";

int main() {
	int port, sockfd;
	char ip[20] = {0};
	port = atoi(get_value(conf, "SERVER_PORT"));

	strcpy(ip, get_value(conf, "SERVER_IP"));
	printf("ip = %s, port = %d\n", ip, port);
	return 0;
}
