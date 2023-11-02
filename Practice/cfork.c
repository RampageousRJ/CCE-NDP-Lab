#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<string.h>
#define MAX 100

void main(){
    int sockfd,retval;
    struct sockaddr_in serveraddr;
    int recbytes,sentbytes;
    char buff[MAX];
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        printf("SOCKET CREATION ERROR");
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    retval = connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(retval==-1){
        printf("CONNECTION ERROR...\n");
        close(sockfd);
        return;
    }
    printf("CONNECTED...\n");
    int pid=fork();
    while(1){
        if(pid>0){
            printf("\n\nParent Process\nPID: %d\tPPID: %d",pid,getppid());
            printf("\nMESSAGE TO SERVER: ");
            gets(buff);
            send(sockfd,&buff,sizeof(buff),0);
            if(strcmp(buff,"exit")==0){
                break;
            }
        }
        else if(pid==0){
            printf("\n\nChild Process\nPID: %d\tPPID: %d",pid,getppid());
            recv(sockfd,&buff,sizeof(buff),0);
            printf("\nRECIEVED: %s",buff);
            if(strcmp(buff,"exit")==0){
                break;
            }
        }
        else{
            printf("Fork Error");
        }
    }
    close(sockfd);
}