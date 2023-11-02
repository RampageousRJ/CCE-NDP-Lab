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
    int sockfd,retval,newsockfd;
    struct sockaddr_in serveraddr,clientaddr;
    int recbytes,sentbytes;
    socklen_t actuallen;
    char buff[MAX];
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        printf("SOCKET CREATION ERROR");
        return;
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);
    serveraddr.sin_addr.s_addr = htons(INADDR_ANY);
    retval = bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(retval==1){
        printf("BINDING ERROR...");
        close(sockfd);
    }
    printf("BIND DONE\n");
    retval = listen(sockfd,1);
    if(retval==-1){
        printf("LISTEN ERROR...");
        close(sockfd);
    }
    printf("LISTENING\n");
    actuallen = sizeof(clientaddr);
    newsockfd = accept(sockfd,(struct sockaddr*)&clientaddr,&actuallen);
    if(newsockfd==-1){
        printf("CONNECTION ERROR...");
        close(sockfd);
        return;
    }
    printf("CONNECTED...");
    int pid=fork();
    while(1){
        if(pid>0){
            printf("\n\nParent Process\nPID: %d\tPPID: %d",pid,getppid());
            recbytes=recv(newsockfd,&buff,sizeof(buff),0);
            printf("\nRECIEVED: %s",buff);
            if(strcmp(buff,"exit")==0){
                break;
            }
        }
        else if(pid==0){
            printf("\n\nChild Process\nPID: %d\tPPID: %d",pid,getppid());
            printf("\nMESSAGE TO CLIENT: ");
            gets(buff);
            send(newsockfd,&buff,sizeof(buff),0);
            if(strcmp(buff,"exit")==0){
                break;
            }
        }
        else{
            printf("Fork Error");
            break;
        }
    }
    close(sockfd);
    close(newsockfd);
}