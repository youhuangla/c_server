/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Sat Dec 31 10:47:52 2022
 ************************************************************************/

#include "head.h"

int socket_create(int port) {
	//printf("port: %d\n", port);
	int server_listen;
	if ((server_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		return -1;
	}
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;

	struct linger m_linger;
	m_linger.l_onoff = 1;
	m_linger.l_linger = 0;
	
	if (setsockopt(server_listen, SOL_SOCKET, SO_LINGER, &m_linger, (socklen_t)sizeof(m_linger)) < 0) {
		return -1;
	}
	int flag = 1;
	if (setsockopt(server_listen, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)) < 0) {
		return -1;
	}
	if (bind(server_listen, (struct sockaddr *)&server, sizeof(server)) < 0) {
		return -1;
	}

	if (listen(server_listen, 20) < 0) {
		return -1;
	}
	return server_listen;
}
