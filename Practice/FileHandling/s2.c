#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90

struct Emp{
    char name[MAXSIZE];
    char reg[MAXSIZE];
    char dept[MAXSIZE];
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
    serveraddr.sin_port=htons(1031);
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
    int arr[MAXSIZE];
    int n,no_of_users=0;
    char temp[1000];
    struct Emp emps[100];
    FILE *f = fopen("database.txt","r");
    while(fgets(temp,1000,f)){
        char *vals[100];
        char *token = strtok(temp,",");
        int i=0;
        while(token!=NULL){
            vals[i++]=token;
            token=strtok(NULL,",");
        }
        struct Emp emp;
        strcpy(emps[no_of_users].name,vals[0]);
        strcpy(emps[no_of_users].reg,vals[1]);
        strcpy(emps[no_of_users].dept,vals[2]);
        no_of_users++;
    }
    while(1){
        int ch;
        recv(ns,&ch,sizeof(ch),0);
        printf(" ");
        printf("\nChoice: %d",ch);
        if(ch==4){
            break;
        }
        else if(ch==2){
            struct Emp e;
            recv(ns,&e,sizeof(e),0);
            emps[no_of_users++]=e;
            FILE *fp = fopen("database.txt","a");
            sprintf(temp,"%s,%s,%s",e.name,e.reg,e.dept);
            fputs("\n",fp);
            fputs(temp,fp);
            fclose(fp);
        }
        else if(ch==1){
            strcpy(temp,"");
            for(int i=0;i<no_of_users;i++){
                char t[MAXSIZE];
                sprintf(t,"\nName: %s\nRegno: %s\nDepartment: %s\n",emps[i].name,emps[i].reg,emps[i].dept);
                strcat(temp,t);
            }
            send(ns,&temp,sizeof(temp),0);
        }
        else if(ch==3){
            char name[100],status[100],dept[100];
            recv(ns,&name,sizeof(name),0);
            printf("\nRecieved: %s",name);
            strcpy(status,"fail");
            int ind=-1;
            for(int i=0;i<no_of_users;i++){
                if(strcmp(emps[i].name,name)==0){
                    strcpy(status,"ok");
                    ind=i;
                }
            }
            send(ns,&status,sizeof(status),0);
            if(strcmp(status,"fail")==0){
                continue;   
            }
            recv(ns,&dept,sizeof(dept),0);
            strcpy(emps[ind].dept,dept);
            strcat(emps[ind].dept,"\n");
            FILE *fp = fopen("database.txt","w");
            for(int i=0;i<no_of_users;i++){
                sprintf(temp,"%s,%s,%s",emps[i].name,emps[i].reg,emps[i].dept);
                fputs(temp,fp);
            }
            fclose(fp);
        }
    }
    close(s);
    close(ns);
}

