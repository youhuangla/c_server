/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Sun Jan  1 20:31:54 2023
 ************************************************************************/

#include "../common/chatroom.h"
#include "../common/tcp_client.h"
#include "../common/common.h"
#include "../common/color.h"
#include "../common/head.h"
#include <stdio.h>

char *conf = "./client.conf";

int main() {
	int port, sockfd;
	struct Msg msg;
	char ip[20] = {0};
	port = atoi(get_value(conf, "SERVER_PORT"));

	strcpy(ip, get_value(conf, "SERVER_IP"));
	printf("ip = %s, port = %d\n", ip, port);
	printf("Press Enter to continue\n");
	getchar();

	if ((sockfd = socket_connect(ip, port)) < 0) {
		perror("socket_connect");
		return 1;
	}
	strcpy(msg.from, get_value(conf, "MY_NAME"));
	msg.flag = 2;
	if (chat_send(msg, sockfd) < 0) {
		return 2;
	}
	struct RecvMsg rmsg = chat_recv(sockfd);

	if (rmsg.retval < 0) {
		fprintf(stderr, "Error!\n");
		return 1;
	}

	printf(GREEN"Server"NONE" : %s", rmsg.msg.message);//server notification
	if (rmsg.msg.flag == 3) {
		close(sockfd);
	}
	pid_t pid;
	if ((pid = fork()) < 0) {
		perror("fork");
	}
	if (pid == 0) {
		system("clear");
		while (1) {
			printf(L_PINK"Please Input Message:"NONE"\n");
			scanf("%[^\n]s", msg.message);
			getchar();
			chat_send(msg, sockfd);
			memset(msg.message, 0, sizeof(msg.message));
			system("clear");
		}
	} else {// parent pid
		wait(NULL);
	}
	return 0;
}
