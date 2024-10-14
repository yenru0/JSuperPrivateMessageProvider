#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <poll.h>

void error_handling(char *message);

int main(int argc, char **argv) {
    int serv_sock;
    int clnt_sock;

    int str_len;
    int sender;
    char message[500];

    // AF_INET의 경우 소켓 주소의 틀을 저장하는 sockaddr_in 구조체 사용
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr; // accept에서 사용
    socklen_t clnt_addr_size;

    char msg[] = "Hello this is server!\n";

    // TCP 프로토콜을 사용하고 IPv4 도메인을 위한 소켓 생성
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket error");

    memset(&serv_addr, 0, sizeof(serv_addr)); // 주소를 초기화
    serv_addr.sin_family = AF_INET; // 타입을 IPv4로
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // ip주소를 host바이트에서 network바이트로 변환하여 저장
    serv_addr.sin_port = htons(12345); //port번호를 host바이트에서 network바이트로 변환하여 저장

    //소켓과 서버 주소를 바인딩
    if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind error");

    //연결 대기열 5개 생성
    if (listen(serv_sock, 5) == -1)
        error_handling("listen error");
    //pollfd 배열 구조체 생성
    struct pollfd fd_list[100];
    int fd_count = 0;

    fd_list[0].fd = serv_sock; //0번째 배열에 listen 지정
    fd_list[0].events = POLLIN; //읽도록
    fd_list[0].revents = 0; //처음엔 0으로 초기화
    fd_count++;

    //나머지 fd_list에는 아직 fd가 없기때문에 -1 저장
    for (int i = 1; i < 100; i++)
        fd_list[i].fd = -1;

    while (1) // 무한정 대기
    {
        int result = poll(fd_list, fd_count, -1);

        if (result > 0) {
            if (fd_list[0].revents == POLLIN) // 서버에 이벤트 발생
            {
                // 클라이언트에게 연결이 올 시 수락
                clnt_addr_size = sizeof(clnt_addr);
                clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_addr, &clnt_addr_size);
                if (clnt_sock == -1)
                    error_handling("accept error");
                fd_list[fd_count].fd = clnt_sock;
                fd_list[fd_count].events = POLLIN;
                recvmsg
                printf("port: %d is conneted\n:", ntohs(clnt_addr.sin_port));
                printf("%s\n", clnt_sock
                fd_count++;
            } else {// 클라이언트에 이벤트 발생
                for (int i = 1; i < fd_count; i++) {
                    switch (fd_list[i].revents) {
                        case 0:
                            break;
                        case POLLIN: {
                            str_len = read(fd_list[i].fd, message, 500);
                            message[str_len] = 0;
                            fputs(message, stdout); // 서버에 받은 메시지 출력
                            fflush(stdout); // 버퍼 비우기
                            sender = fd_list[i].fd;
                            for (int i = 1; i < fd_count; i++) {
                                if (sender != fd_list[i].fd) {
                                    // 전송 클라이언트를 제외한 나머지에 모두 전송
                                    write(fd_list[i].fd, message, strlen(message));
                                }
                            }
                        }
                    }
                }
            }
        } else
            error_handling("poll error");
    }

    //소켓 닫기
    for (int i = fd_count - 1; fd_count != 0; i--)
        close(fd_list[i].fd);

    return (0);
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}