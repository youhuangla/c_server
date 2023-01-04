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
#include <unistd.h>

char *conf = "./client.conf";

int sockfd;

char logfile[50] = {0};

void logout(int signalnum) {
	// close the connection after receive ctrl+c(sigint)
	close(sockfd);
	printf("You have logout!\n");
	exit(1);
	//printf("recv a signal\n");
	//return NULL;
}

int main() {
	int port;
	struct Msg msg;
	char ip[20] = {0};
	port = atoi(get_value(conf, "SERVER_PORT"));

	strcpy(ip, get_value(conf, "SERVER_IP"));
	strcpy(logfile, get_value(conf, "LOG_FILE"));


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
		sleep(2);
		signal(SIGINT, logout);
		system("clear");
		char c = 'a';
		while (c != EOF) {
			printf(L_PINK"Please Input Message:"NONE"\n");
			scanf("%[^\n]s", msg.message);
			c = getchar();
			msg.flag = 0;
			//printf("msg.flag = %d\n", msg.flag);
			//sleep(4);
			if (msg.message[0] == '@') {
				//printf("private chat mark\n");
				//sleep(4);
				msg.flag = 1; //private chat
			}
			chat_send(msg, sockfd);
			memset(msg.message, 0, sizeof(msg.message));
			system("clear");
		}
		close(sockfd);
	} else {// parent pid
		//FILE *log_fp = fopen(logfile, "w");
		//struct RecvMsg rmsg;
		freopen(logfile, "a+", stdout);
		while (1) {
			//receive message
			rmsg = chat_recv(sockfd);
			if (rmsg.retval < 0) {
				printf("Error in Server!\n");
				break;
			}
			//printf("client.c 102\n");//print in chat.log?
			//sleep(5);
			if (rmsg.msg.flag == 0) {
				printf(L_BLUE"%s"NONE" : %s\n", rmsg.msg.from, rmsg.msg.message);
			} else if (rmsg.msg.flag == 2) {
				//printf("client.c 107\n");
				printf(YELLOW"Notification: "NONE" %s\n", rmsg.msg.message);
			} else if (rmsg.msg.flag == 1) {
				printf(L_BLUE"%s"L_GREEN"*"NONE" : %s\n", rmsg.msg.from, rmsg.msg.message);//?
				//printf("Private Chat!\n");
			} else {
				printf("Flag Error!\n");
			}
			fflush(stdout);
		}
		wait(NULL);
		close(sockfd);
	}
	return 0;
}
