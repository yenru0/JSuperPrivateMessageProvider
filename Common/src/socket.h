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
#include <vector>
#include <thread>

#define BUFSIZE 4096

void read_childproc(int sig);

void error_handling(const char *message);

class Socket {
protected:
    int fd;

public:

    Socket() { fd = socket(AF_INET, SOCK_STREAM, 0); }

    Socket(int clnt_sock) { fd = clnt_sock; }

    virtual ~Socket() { close(); }

    int get_fd() const { return fd; }

    void close() const { ::close(fd); }
};

class ServerSocket : public Socket {
protected:
    struct sockaddr_in server_addr;

public:
    ServerSocket();

    ~ServerSocket() override;

    bool bindSocket(uint16_t port);

    bool listenSocket(int num);

    int acceptSocket();

    void closeListenSocket();
};

class ClientSocket : public Socket {
protected:
    struct sockaddr_in server_addr;

public:
    ClientSocket();

    void set_address(const char *ip, int16_t port);

    void connectSocket();

    void sendMsg(std::string msg);

};

