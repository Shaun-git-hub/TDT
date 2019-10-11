#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>// 网络相关头文件
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#define SERVER_PORT 8888

int main(int argc, char **argv)
{
    int sfd, cfd;
    int iRet;
    struct sockaddr_in tServerAddr;
    struct sockaddr_in tClientAddr;
    ssize_t iRecvLen;
    socklen_t iAddrLen;
    unsigned char ucRecvBuf[1000];

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sfd)
    {
        printf("socket error!\n");
        return -1;
    }

    tServerAddr.sin_family  = AF_INET;
    tServerAddr.sin_port    = htons(SERVER_PORT);
    tServerAddr.sin_addr.s_addr = INADDR_ANY;
    memset(tServerAddr.sin_zero, 0, 8);

    iRet = bind(sfd, (const struct sockaddr *)&tServerAddr, 
                sizeof(tServerAddr));
    if (-1 == iRet) 
    {
        printf("bind error!\n");
        return -1;
    }
    
    iRet = listen(sfd, 1);
    if (-1 == iRet)
    {
        printf("listen error!\n");
        return -1;
    }

    while (1)
    {
        iAddrLen = sizeof(struct sockaddr);
        cfd = accept(sfd, (struct sockaddr *)&tClientAddr,
                    &iAddrLen );
        if (-1 != cfd)
        {
            printf("接受");
            iRecvLen = recv(cfd, &ucRecvBuf, 999, 0);
            if (iRecvLen <= 0)
            {
                close(cfd);
                return -1;
            }
            else
            {
                ucRecvBuf[iRecvLen] = '\0';
                printf("Get Msg Frome Client : %s\n",
                       ucRecvBuf);

            }

        }
        // ssize_t recv(int sockfd, void *buf, size_t len, int flags);
    }
}






































