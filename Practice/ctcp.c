#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>
#define MAX 100

void main(){
    int sockfd,retval;
    struct sockaddr_in serveraddr;
    int recdbytes,sentbytes;
    int n;
    char buff[MAX];
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        printf("Socket Creation Error");
    }
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(3388);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    retval = connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(retval==-1){
        printf("CONNECTION ERROR\n");
        close(sockfd);
        return;
    }
    printf("Connected\n");
    while(1){
        printf("\nEnter message to server: ");
        gets(buff);
        sentbytes = send(sockfd,&buff,sizeof(buff),0);
        if(sentbytes==-1){
            printf("SENDING ERROR");
        }
        if(strcmp(buff,"exit")==0){
            printf("EXITING...\n");
            break;
        }
        sleep(1);
        recdbytes = recv(sockfd,&buff,sizeof(buff),0);
        if(recdbytes==-1){
            printf("RECEIVE ERROR");
        }
        if(strcmp(buff,"exit")==0){
            printf("EXITING...\n");
            break;
        }
        printf("%s RECIEVED...\n",buff);
    }
    close(sockfd);
}