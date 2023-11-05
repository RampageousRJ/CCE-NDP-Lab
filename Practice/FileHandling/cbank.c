#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#define MAXSIZE 90

struct Users{
    char name[MAXSIZE];
    char pass[MAXSIZE];
    int amount;
};

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
    serveraddr.sin_port=htons(31200);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    retval=connect(s,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(retval==-1){
        printf("Connection error");
        close(s);
        exit(0);
    }
    int n=7;
    int sum=0;
    char temp[1000],name[MAXSIZE],pass[MAXSIZE],status[MAXSIZE];
    strcpy(status,"fail");
    while(1){
        if(strcmp(status,"fail")==0){
            printf("Enter name: ");
            scanf("%s",name);
            printf("Enter pass: ");
            scanf("%s",pass);
            send(s,name,sizeof(name),0);
            send(s,pass,sizeof(pass),0);
            recv(s,status,sizeof(status),0);
            if(strcmp(status,"fail")==0){
                printf("\nINVALID CREDENTIALS...");
                continue;
            }
        }
        int ch;
        printf("\n\nMENU\n1.Add User\n2.Deposit\n3Withdraw\n4.Exit\nEnter your choice: ");
        scanf("%d",&ch);
        send(s,&ch,sizeof(ch),0);
        if(ch==1){
            struct Users u;
            printf("Enter name: ");
            scanf("%s",u.name);
            printf("Enter pass: ");
            scanf("%s",u.pass);
            printf("Enter amount: ");
            scanf("%d",&u.amount);
            send(s,&u,sizeof(u),0);
            printf("Inserted Successfully...");
        }
        else if(ch==2){
        }
        if(ch==4){
            printf("THANKS FOR CHOOSING US...");
            break;
        }
    }
    close(s);
}