# c_server



```bash
sudo ufw allow 8888
```

[阿里云服务器开放端口教程（通过配置安全组规则）\-阿里云开发者社区](https://developer.aliyun.com/article/767328)

```
youhuangla@Ubuntu server % ./client  39.96.76.xxx 8888                                                        [1]
Socket create.
Socket connect.
```

```bash
youhuangla@Ubuntu server % ./server 8888                                                                    [130]
Socket create.
Socket bind.
Socket before accept.
Socket after accept.
Socket received.
name: suyelu
Socket before accept.
^C
```

扫描公共服务器可用[Nmap: the Network Mapper \- Free Security Scanner](https://nmap.org/)

用 sleep-client (连接上socket后不发信息)连上server端后，其他客户端程序也无法连接，所以要使用多线程、多进程。

多进程见 fork-server. 但是多进程会产生僵尸进程。

多线程封装成echo服务器：
 
```bash
youhuangla@Ubuntu server % ./a.out 8888                                                                       [2]
Socket create.
Socket bind.
New Client Login
recv: abc

Success in ECHO!
^C
```

```
youhuangla@DESKTOP-0O633M1:~$ telnet 39.96.76.xxx 8888
Trying 39.96.76.106...
Connected to 39.96.76.106.
Escape character is '^]'.
You are Here
abc
ABC
Connection closed by foreign host.
```

地址重用与延迟关闭的实现

```bash
youhuangla@Ubuntu server % ./a.out 8888                                                                   [0]
New Client Login
recv: 1abc

Success in ECHO!
^C
```

```
youhuangla@DESKTOP-0O633M1:~$ telnet 39.96.76.xxx 8888
Trying 39.96.76.106...
Connected to 39.96.76.106.
Escape character is '^]'.
You are Here
1abc
1ABC
Connection closed by foreign host.
```

非阻塞IO

```c
	sleep(1);// attention: if this line not added
```

```bash
youhuangla@Ubuntu client % ./a.out 39.96.76.106 8888                                                          [0]
Socket create.
recv: You are Here

```

```bash
youhuangla@Ubuntu server % ./a.out  8888                                                                    [130]
New Client Login
error in recv!
: Success

```

```c
	//sleep(1);// attention: if this line not added
```

```bash
youhuangla@Ubuntu client % ./a.out 39.96.76.106 8888                                                          [0]
Socket create.
recv: 
```

```bash
youhuangla@Ubuntu server % ./a.out  8888                                                                    [130]
New Client Login
error in recv!
: Success

```

client打印ip和port

```bash
youhuangla@Ubuntu client % ./client                                                                           [0]
ip = 39.96.76.106, port = 8888
```

一个史诗级bug：

```server.conf
SERVER_PORT=8888

```

```server.conf
SERVER_PORT=8888
```

区别：没有一个换行，会造成缺少一个字符，port会显示为888。。而888在1024以下，需要root，建议多用printf调试。

```bash
youhuangla@Ubuntu server % ./server                   [0]
socket_create: Permission denied
```

修改好后：

```bash
youhuangla@Ubuntu client % ./client                                                                           [0]
ip = 39.96.76.xxx, port = 8888
Socket create.
```

```bash
youhuangla@Ubuntu server % ./server                                                                           [0]
Client login!
```

server.c中work函数实现

```bash
youhuangla@Ubuntu client % ./client                                                                           [0]
ip = 39.96.76.xxx, port = 8888
Socket create.
```

```bash
youhuangla@Ubuntu server % ./server                                                                           [0]
Login: yhl 

```

chatroomv2

```bash
youhuangla@Ubuntu client % ./client                                                                           [0]
ip = 39.96.76.xxx, port = 8888
Socket create.
Server : Welcome to this chatroom!%    
```

```bash
youhuangla@Ubuntu server % ./server                                                                           [0]
Login : yhl
Logout: yhl 
```

Chatroom talk

```bash
youhuangla@Ubuntu server % ./server                                                                         [130]
Login : yhl
yhl : Hello world!

```

找未退出的客户端

```bash
youhuangla@Ubuntu thread-server % ps -ef | grep client  
```

让客户端显示公聊信息，并录入 chat.log 。

客户端1

```bash
youhuangla@Ubuntu client % ./client                                                                           [0]
ip = 39.96.76.106, port = 8888
Press Enter to continue

Socket create.
Server : Welcome to this chatroom!
Please Input Message:
yhl2 : hi
hallo
Please Input Message:
yhl : hallo
```

客户端2

```bash
youhuangla@DESKTOP-0O633M1:~/c_server/client$ ./client
ip = 39.96.76.106, port = 8888
Press Enter to continue

Socket create.
Server : Welcome to this chatroom!
Please Input Message:
hi
Please Input Message:
yhl2 : hi
yhl : hallo
```

服务器

```bash
youhuangla@Ubuntu server % ./server                                                                           [0]
Login : yhl
Login : yhl2
yhl2 : hi
yhl : hallo
```