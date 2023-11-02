#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define MAXSIZE 90

void main()
{
    int sockfd, retval;
    int recedbytes, sentbytes1, sentbytes2, sentbytes3;
    struct sockaddr_in serveraddr;

    char buff[MAXSIZE];
    char nbuff[MAXSIZE];
    char abuff[MAXSIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("\nSocket Creation Error");
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3390);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    retval = connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    if (retval == -1)
    {
        printf("Connection error");
    }
        strcpy(buff, "");
        printf("\n\nEnter alphanumeric string: ");
        gets(buff);
        int n = strlen(buff);
        send(sockfd, buff, sizeof(buff), 0);
        send(sockfd, &n, sizeof(n), 0);
        sleep(2);
        recv(sockfd, &nbuff, sizeof(nbuff), 0);
        recv(sockfd, &abuff, sizeof(abuff), 0);
        printf("\nNUMERIC: %s",abuff);
        printf("\nALPHABETICAL: %s\n\n",nbuff);
    close(sockfd);
}
