#include <iostream>
#include <thread>

#include "socket.h"
#include "server.h"

#define MAX_CLNT 32

MessageProvider::MessageProvider() {
    serv_sock = new ServerSocket();
    clnt_socks = new Socket *[MAX_CLNT];
    //clnt_threads = new std::thread *[MAX_CLNT];
    clnt_recv_buffer = new char *[MAX_CLNT];

}

MessageProvider::~MessageProvider() {
    delete serv_sock;
    for (int i = 0; i < MAX_CLNT; i++) {
        if (clnt_socks[i] != nullptr) {
            delete clnt_socks[i];
            //delete clnt_threads[i];
            delete[] clnt_recv_buffer[i];
        }

    }
    delete[] clnt_socks;
    //delete[] clnt_threads;
    delete[] clnt_recv_buffer;
}

void MessageProvider::run() {
    acceptProcess();
}

bool MessageProvider::bindProcess(uint16_t port) {
    return serv_sock->bindSocket(port);
}

bool MessageProvider::listenProcess(int num) {
    return serv_sock->listenSocket(num);
}

int MessageProvider::acceptProcess() { // return fd of clnt socket
    while (true) {
        int sck = serv_sock->acceptSocket();
        int idx = clientInitProcess(sck);
    }
}


int MessageProvider::clientInitProcess(int clnt_sock) {
    while (clnt_socks[clnt_counter] != nullptr) {
        clnt_counter++;
    }
    clnt_socks[clnt_counter] = new Socket(clnt_sock);
    clnt_recv_buffer[clnt_counter] = new char[BUFSIZE];
    std::thread t = std::thread(MessageProvider::clientInteractProcess, this, clnt_counter);
    t.detach();
    return clnt_counter;
}

bool MessageProvider::clientRecvProcess(int idx) {
    memset(clnt_recv_buffer[idx], 0, BUFSIZE);
    if (::recv(clnt_socks[idx]->get_fd(), clnt_recv_buffer[idx], BUFSIZE, 0) > 0) {
        return true;
    } else {
        return false;
    }
}

void MessageProvider::clientCloseProcess(int idx) {
    delete clnt_socks[idx];
    delete clnt_recv_buffer[idx];
    clnt_socks[idx] = nullptr;
}

void MessageProvider::clientInteractProcess(MessageProvider *that, int idx) {
    while (that->clientRecvProcess(idx)) {
        std::cout << idx << ": " << that->clnt_recv_buffer[idx] << std::endl;
    }

    that->clientCloseProcess(idx);

    std::cout << idx << ":: quit" << std::endl;
}
