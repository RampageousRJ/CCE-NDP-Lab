#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<string.h>
#define MAX 100

void main(){
    int sockfd,newsockfd,retval;
    int n;
    char buff[MAX];
    int recdbytes,sentbytes;
    socklen_t actual_length;
    struct sockaddr_in serveraddr,clientaddr;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        printf("Socket Creation Error");
        return;
    }
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(3388);
    serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
    retval = bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(retval==1){
        printf("Binding Error");
        close(sockfd);
    }
    retval = listen(sockfd,1);
    if(retval==-1){
        printf("Listen Error");
        close(sockfd);
    }
    actual_length = sizeof(clientaddr);
    newsockfd=accept(sockfd,(struct sockaddr*)&clientaddr,&actual_length);
    if(newsockfd==-1){
        printf("New Socket Creation Error");
        close(sockfd);
    }
    printf("Connected\n");
    while(1){
        recdbytes = recv(newsockfd,&buff,sizeof(buff),0);
        if(recdbytes==-1){
            printf("RECEIVE ERROR");
        }
        if(strcmp(buff,"exit")==0){
            printf("EXITING...\n");
            break;
        }
        printf("%s RECIEVED...\n",buff);
        printf("\nEnter message to client: ");
        gets(buff);
        sentbytes = send(newsockfd,&buff,sizeof(buff),0);
        if(sentbytes==-1){
            printf("SENDING ERROR");
        }
        if(strcmp(buff,"exit")==0){
            printf("EXITING...\n");
            break;
        }
    }
    
    close(newsockfd);
    close(sockfd);
}