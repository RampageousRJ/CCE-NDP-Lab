#include <stdio.h>
#include <stdlib.h>

int main(){
    char buff[100];
    printf("Enter sentence to append: ");
    gets(buff);
    FILE *fp = fopen("sample.txt","a");
    fputs("\n",fp);
    fputs(buff,fp);
    fclose(fp);
    return 0;
}