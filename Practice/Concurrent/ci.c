#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#define MAXSIZE 50

void main(){
    int s,retval;
    int recedbytes,sentbytes;
    struct sockaddr_in serveraddr;
    char buff[MAXSIZE];
    s=socket(AF_INET,SOCK_STREAM,0);
    if(s==-1){
        printf("\nSocket Creation Error");
    }
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(5556);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    retval=connect(s,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(retval==-1){
        printf("Connection error");
        close(s);
        exit(0);
    }
    while(1){
        printf("Enter string: ");
        gets(buff);
        send(s,buff,sizeof(buff),0);
        sleep(1);
        if(strcmp(buff,"exit")==0){
            break;
        }
    }
    close(s);
}