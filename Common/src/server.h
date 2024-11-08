#pragma once

#include "socket.h"



class MessageProvider {
protected:
    ServerSocket *serv_sock;
    Socket **clnt_socks;
    //std::thread **clnt_threads;
    char **clnt_recv_buffer;

    std::thread run_thread;

    int clnt_counter = 0;
public:
    MessageProvider();

    ~MessageProvider();

    void run();

    bool bindProcess(uint16_t port);

    bool listenProcess(int num);

    int acceptProcess();

    void clientCloseProcess(int idx);

    static void clientInteractProcess(MessageProvider* that, int idx);

    int clientInitProcess(int clnt_sock);

    bool clientRecvProcess(int idx);

    void sendMsgToAll();

    void sendMsgTo(int idx);

    void recvMsg(int idx);

};
