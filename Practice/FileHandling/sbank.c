#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90

struct Users{
    char name[MAXSIZE];
    char pass[MAXSIZE];
    char amount[MAXSIZE];
};

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
    serveraddr.sin_port=htons(31200);
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
    printf("SOCKET LISTENING...\n");
    actuallen=sizeof(clientaddr);
    ns=accept(s,(struct sockaddr*)&clientaddr,&actuallen);
    if(ns==-1){
        close(s);
    }
    printf("CONNECTED...\n");
    char temp[1000];
    int no_of_users=0;
    struct Users users[MAXSIZE];
    FILE *f = fopen("db.txt","r");
    while(fgets(temp,1000,f)){
        // printf("\n%s",temp);
        char *vals[MAXSIZE];
        char *token = strtok(temp,",");
        int i=0;
        while(token!=NULL){
            vals[i++]=token;
            token = strtok(NULL,",");
        }
        strcpy(users[no_of_users].name,vals[1]);
        strcpy(users[no_of_users].pass,vals[2]);
        strcpy(users[no_of_users].amount,vals[0]);
        no_of_users++;
    }
    printf("Here..."); 
    fclose(f); 
    char name[MAXSIZE],pass[MAXSIZE],status[MAXSIZE];
    while(1){
        printf("Hello?");
        recv(s,name,sizeof(name),0);
        recv(s,pass,sizeof(pass),0);
        printf("Recieved: %s %s",name,pass);
        strcpy(status,"fail");
        for(int i=0;i<no_of_users;i++){
            if(strcmp(users[i].name,name)==0 && strcmp(users[i].pass,pass)==0){
                strcpy(status,"ok");
            }
        }
        send(s,status,sizeof(status),0);
        int ch=-1;
        while(1){
            recv(ns,&ch,sizeof(ch),0);
            printf(" ");
            printf("\nChoice: %d",ch);
            if(ch==4){
                break;
            }
            if(ch==1){
                struct Users u;
                recv(ns,&u,sizeof(u),0);
                users[no_of_users++]=u;
                FILE *fp = fopen("db.txt","w");
                for(int i=0;i<no_of_users;i++){
                    sprintf(temp,"%s,%s,%s",users[i].name,users[i].pass,users[i].amount);
                    fputs(temp,fp);
                    fputs("\n",fp);
                }
                fclose(fp);
                printf("Inserted Successfully...");
            }
        }
        
    }
    close(s);
    close(ns);
}

