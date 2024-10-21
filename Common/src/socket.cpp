#include "socket.h"

void read_childproc(int sig) {
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    printf("removed proc id : %d \n", pid);
}

void error_handling(const char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

ServerSocket::ServerSocket() {
    clnt_sock = -1;
    recv_buffer = new char[BUFSIZE];
}

bool ServerSocket::bindSocket(uint16_t port) {
    bzero((char *) &server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    int flag = bind(fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (flag == -1)
        return false;
    else
        return true;
}

bool ServerSocket::listenSocket(int num) {
    int flag = listen(fd, num);
    if (flag == -1)
        return false;
    else
        return true;
}

bool ServerSocket::acceptSocket() {
    if (clnt_sock != -1) return false; // only one client
    sockaddr_in addr;
    socklen_t addr_size;
    addr_size = sizeof(addr);
    clnt_sock = accept(fd, (struct sockaddr *) &addr, &addr_size);
    if (clnt_sock == -1)
        return false;
    else
        return true;
}

bool ServerSocket::recvMsg() {
    memset(recv_buffer, 0, BUFSIZE);
    if (recv(clnt_sock, recv_buffer, BUFSIZE, 0) > 0) {
        return true;
    }
    return false;
}

std::string ServerSocket::getBufferedMsg() {
    return std::string(recv_buffer);
}