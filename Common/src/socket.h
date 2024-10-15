#pragma once

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <csignal>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#define BUFSIZE 4096

void read_childproc(int sig);

void error_handling(char *message);

class Socket {
protected :
    int fd;

public:
    Socket() { fd = socket(AF_INET, SOCK_STREAM, 0); }
};

class ServerSocket : public Socket {
protected:
    int clnt_sock;
public:
    ServerSocket() : Socket() {};

    bool bindSocket(char *port);

    bool listenSocket(int num);

    bool acceptSocket();

    bool sendFile(char *filename);

    void closeListenSocket() { close(fd); }

    void closeAcceptSocket() { close(clnt_sock); }
};

