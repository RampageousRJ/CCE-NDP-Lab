#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 100

struct Emp{
    char name[MAXSIZE];
    char reg[MAXSIZE];
    char dept[MAXSIZE];
};

int main(){
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
    for(int i=0;i<no_of_users;i++){
        printf("\n%s\n",emps[i].name);
        printf("%s\n",emps[i].reg);
        printf("%s\n",emps[i].dept);
    }
    return 0;
}