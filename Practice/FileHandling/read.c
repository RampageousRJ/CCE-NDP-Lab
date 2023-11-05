#include <stdio.h>
#include <stdlib.h>

int main(){
    char buff[100];
    FILE *fp = fopen("sample.txt","r");
    while(fgets(buff,100,fp)!=NULL){
        printf("%s",buff);
    }
    fclose(fp);
    return 0;
}