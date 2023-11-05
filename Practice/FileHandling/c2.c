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

struct Emp{
    char name[MAXSIZE];
    char reg[MAXSIZE];
    char dept[MAXSIZE];
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
    serveraddr.sin_port=htons(1031);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    retval=connect(s,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(retval==-1){
        printf("Connection error");
        close(s);
        exit(0);
    }
    int n=7;
    int sum=0;
    char temp[1000];
    while(1){
        int ch;
        printf("\n\nMENU\n1.Display\n2.Enter Details\n3.Edit\n4.Exit\nEnter your choice: ");
        scanf("%d",&ch);
        send(s,&ch,sizeof(ch),0);
        if(ch==1){
            printf("\n\n");
            recv(s,&temp,sizeof(temp),0);
            printf("%s",temp);
        }
        
        else if(ch==2){
            struct Emp emp;
            printf("\nEnter name: ");
            scanf("%s",emp.name);
            printf("\nEnter regno: ");
            scanf("%s",emp.reg);
            printf("\nEnter department: ");
            scanf("%s",emp.dept);
            send(s,&emp,sizeof(emp),0);
            printf("Added Successfuly!");
        }
        else if(ch==3){
            char name[100],status[100],dept[100];
            printf("Enter name: ");
            scanf("%s",name);
            send(s,&name,sizeof(name),0);
            recv(s,&status,sizeof(status),0);
            if(strcmp(status,"fail")==0){
                printf("\nUser not found...");
                continue;   
            }
            printf("\nEnter new department: ");
            scanf("%s",dept);
            send(s,&dept,sizeof(dept),0);
            printf("\nUpdated Successfully...");
        }
        else if(ch==4){
            printf("Thank you for choosing us!");
            break;
        }
    }
    close(s);
}