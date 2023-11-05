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
    serveraddr.sin_port=htons(5556);
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
    int no_of_clients=0;
    while(1){
        actuallen = sizeof(clientaddr);
        ns = accept(s,(struct sockaddr*)&clientaddr,&actuallen);
        no_of_clients++;
        
        if(no_of_clients>2){
            printf("\nCannot accept another client...");
            exit(0);
        }
        int pid=fork();
        if(pid==0){
            printf("\nWelcome Client%d",no_of_clients);
            close(s);
            while(1){
                recv(ns,buff,sizeof(buff),0);
                printf("\nRECIEVED %d: %s",no_of_clients,buff);
                if(strcmp(buff,"exit")==0){
                    break;
                }
            }
            no_of_clients--;
            exit(0);
        }
        close(ns);
    }
    close(s);
}

