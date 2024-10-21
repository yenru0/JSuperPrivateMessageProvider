#pragma once

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <csignal>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>

#define BUFSIZE 4096

void read_childproc(int sig);

void error_handling(const char *message);

class Socket {
protected :
    int fd;
public:
    Socket() { fd = socket(AF_INET, SOCK_STREAM, 0); }

    void closeSocket() { close(fd); }
};

class ServerSocket : public Socket {
protected:
    int clnt_sock;
    struct sockaddr_in server_addr;
    char *recv_buffer;
public:
    ServerSocket();

    bool bindSocket(uint16_t port);

    bool listenSocket(int num);

    bool acceptSocket();

    void closeListenSocket() { closeSocket(); }

    void closeAcceptSocket() {
        close(clnt_sock);
        clnt_sock = -1;
    }

    bool recvMsg();

    std::string getBufferedMsg();
};

