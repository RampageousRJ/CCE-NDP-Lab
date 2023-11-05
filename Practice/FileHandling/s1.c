#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 7
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
    serveraddr.sin_port=htons(1234);
    serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
    retval=bind(s,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(retval==1){
        printf("Binding error");
        close(s);
    }

    retval=listen(s,1);
    if(retval==-1){
        close(s);
    }
    actuallen=sizeof(clientaddr);
    ns=accept(s,(struct sockaddr*)&clientaddr,&actuallen);
    if(ns==-1){
        close(s);
    }
    printf("CONNECTED...\n");
    int arr[MAXSIZE];
    int n;
    while(1){
        int sum=0;
        recv(ns,arr,sizeof(arr),0);
        recv(ns,&n,4,0);
        printf("RECIEVED N: %d",n);
        char temp[MAXSIZE];
        FILE *fp = fopen("test.txt","w");
        for(int i=0;i<n;i++){
            sum+=arr[i];
            sprintf(temp,"%d",arr[i]);
            fputs(temp,fp);
            fputs(" ",fp);
        }
        sprintf(temp,"= %d",sum);
        fputs(temp,fp);
        fclose(fp);
        send(ns,&sum,4,0);
        printf("SENT SUM: %d",sum);
    }
    close(s);
    close(ns);
}

