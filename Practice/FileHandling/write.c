#include <stdio.h>
#include <stdlib.h>

int main(){
    int buff[100]={103,1,2,3,4,500};
    FILE *fp = fopen("sample.txt","w");
    char temp[100];
    for(int i=0;i<6;i++){
        sprintf(temp,"%d",buff[i]);
        fputs(temp,fp);
        fputs(" ",fp);
    }
    fclose(fp);
    return 0;
}