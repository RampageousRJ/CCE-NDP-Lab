#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 50
void main(){
    int s,ns,retval;
    socklen_t actuallen;
    int recedbytes,sentbytes;
    struct sockaddr_in serveraddr,clientaddr;

    char buff[MAXSIZE];
    int a=0;
    s=socket(AF_INET,SOCK_STREAM,0);
    if(s==-1){
        printf("\nSocket creation error");
    }

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(5555);
    serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
    retval=bind(s,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(retval==1){
        printf("Binding error");
        close(s);
    }
    retval=listen(s,10);
    if(retval==-1){
        close(s);
    }
    printf("\nListening...");
    while(1){
        actuallen = sizeof(clientaddr);
        ns = accept(s,(struct sockaddr*)&clientaddr,&actuallen);
        printf("\nConnected...");
        while(1){
            recv(ns,buff,sizeof(buff),0);
            printf("\nRECIEVED: %s",buff);
            if(strcmp(buff,"exit")==0){
                break;
            }
        }
        printf("\nDisconnected...\n");
        close(ns);
    }
    close(s);
}

