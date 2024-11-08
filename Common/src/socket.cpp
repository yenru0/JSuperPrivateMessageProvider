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
}

ServerSocket::~ServerSocket() {
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

void ServerSocket::closeListenSocket() {
    this->close();
}

int ServerSocket::acceptSocket() {
    sockaddr_in addr;
    socklen_t addr_size;
    addr_size = sizeof(addr);
    int clnt_sock = accept(fd, (struct sockaddr *) &addr, &addr_size);
    if (clnt_sock == -1)
        return -1;
    else {
        return clnt_sock;
    }
}


ClientSocket::ClientSocket() {
}

void ClientSocket::set_address(const char *ip, int16_t port) {
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &(server_addr.sin_addr));
}

void ClientSocket::connectSocket() {
    connect(fd, (sockaddr *) &(server_addr), sizeof(server_addr));
}

void ClientSocket::sendMsg(std::string msg) {
    ::send(fd, msg.c_str(), sizeof(msg), 0);
}


/*
void ServerSocket::closeAcceptSocket(int idx) {
    delete clnt_socks[idx];
    clnt_socks[idx] = nullptr;
}



bool ServerSocket::recvMsg(int idx) {
    memset(recv_buffer, 0, BUFSIZE);
    if (::recv(clnt_socks[idx]->get_fd(), recv_buffer, BUFSIZE, 0) > 0) {
        return true;
    }
    return false;
}

std::string ServerSocket::getBufferedMsg() {
    return std::string(recv_buffer);
}
 */