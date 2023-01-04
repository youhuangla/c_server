/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Sun Jan  1 20:18:42 2023
 ************************************************************************/

#include "../common/head.h"
#include "../common/common.h"
#include "../common/tcp_server.h"
#include "../common/chatroom.h"
#include "../common/color.h"

struct User{
	char name[20];
	int online;// flag of online
	pthread_t tid;
	int fd;
};

char *conf = "./server.conf";

struct User *client;

void *work(void *arg) {
	int *sub = (int *)arg;
	int client_fd = client[*sub].fd;
	struct RecvMsg rmsg;
	printf(GREEN"Login "NONE": %s\n", client[*sub].name);
	while (1) {
		rmsg = chat_recv(client_fd);
		if (rmsg.retval < 0) {
			printf(PINK"Logout:"NONE" %s \n", client[*sub].name);
			close(client_fd);
			client[*sub].online = 0;
			return NULL;
		}
		printf(BLUE"%s"NONE" : %s\n", rmsg.msg.from, rmsg.msg.message);
	}
	//printf("A client login!\n");
	return NULL;
}

int find_sub() {
	for (int i = 0; i < MAX_CLIENT; i++) {
		if (!client[i].online) {
			return i;
		}
	}
	return -1;
}

bool check_online(char *name) {
	for (int i = 0; i < MAX_CLIENT; i++) {
		/*
		printf("check_online %d\n", i);
		if (strlen(client[i].name) != 0) {
			printf("client[%d].name: %s ", i, client[i].name);
		}
		*/
		if (client[i].online && !strcmp(name, client[i].name)) {// struct User initialised by calloc, so the origin is 0
			printf(YELLOW"Warning:"NONE": %s is online\n", name);//Only when login again
			return true;
		}
	}
	return false;
}

int main(int argc, char **argv) {
	int port, server_listen;
	int fd;
	struct RecvMsg recvmsg;
	struct Msg msg;
	port = atoi(get_value(conf, "SERVER_PORT"));
	client = (struct User *)calloc(MAX_CLIENT, sizeof(struct User));// clear with 0
	if ((server_listen = socket_create(port)) < 0) {
		perror("socket_create");
		return 1;
	}
	//printf("Socket create.server_listen is %d\n", server_listen);
	while (1) {
		//printf("line 60\n");
		if ((fd = accept(server_listen, NULL, NULL)) < 0) {
			perror("accept");
			continue;
		}
		//printf("Accept\n");
		recvmsg = chat_recv(fd);
		if (recvmsg.retval < 0) {
			close(fd);
			continue;
		}

		//Bug: if a people not send his first img, it will block, so we should make a time limit
		if (check_online(recvmsg.msg.from)) {
			msg.flag = 3;
			strcpy(msg.message, "You have already Login!");
			chat_send(msg, fd);
			close(fd);
			continue;
			//refuse connection:
		}
		msg.flag = 2;
		strcpy(msg.message, "Welcome to this chatroom!");
		chat_send(msg, fd);
		int sub;
		sub = find_sub();
		client[sub].online = 1;
		client[sub].fd = fd;
		strcpy(client[sub].name, recvmsg.msg.from);
		pthread_create(&client[sub].tid, NULL, work, (void *)&sub);
	}
	
	return 0;
}
