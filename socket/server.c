#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>


int main()
{
    int sfd;
    struct sockaddr_in my_addr;

    sfd = socket(AF_INET,SOCK_STREAM, 0);
    if(sfd == -1){
        printf("socket err");
    }
    bind( sfd, const struct sockaddr *__addr, socklen_t __len );

   
    
        
    
}
