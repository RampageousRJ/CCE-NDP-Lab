#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#define MAX_LEN 100
void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[1000];
    int index = 0;
    int owlen;
    owlen = strlen(oldWord);
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, newWord);
        strcat(str, temp + index + owlen);
    }
}
int main()
{
	int s,r,recb,sntb,ns,a=0;
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50];

	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(3388);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded.");

	r=listen(s,1);
	if(r==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket listening.\n");

	len=sizeof(client);

	ns=accept(s,(struct sockaddr*)&client, &len);
	if(ns==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket accepting.\n");

	recb=recv(ns,buff,sizeof(buff),0);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		close(ns);
		exit(0);
	}	
	printf("\nFile Name Recieved!\n");
	/*printf("%s", buff);
	printf("\n\n");
	scanf("%s", buff);*/
	char fil[50];
	if( access( buff, F_OK ) != -1 ) {
    // file exists
		strcpy(fil,buff);
		strcpy(buff,"File exists");
	} else {
    // file doesn't exist
		strcpy(buff,"File does not exist!");
	}

	sntb=send(ns,buff,sizeof(buff),0);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		close(ns);
		exit(0);
	}
	if(strcmp(buff,"File does not exist!")==0)
	{
		close(s);
		close(ns);
		exit(0);
	}
	int ch=0;
	while(ch!=4){
	recb=recv(ns,buff,sizeof(buff),0);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		close(ns);
		exit(0);
	}	
	ch = buff[0];
	int i,n,n1,n2,j;
	char str[50],str1[50],str2[50];
	char temp[MAX_LEN];
    char **arr = NULL; // String List
    int rows = 0;
	switch(ch)
	{
		case 1:
		printf("\nSearching..\n");
		n=buff[1];
		for(i=0;i<n;i++)
			str[i]=buff[i+2];
		str[n]='\0';
		FILE *fp;
		int row = 1;
		int find_result = 0;
		char temp[512];
		if((fp = fopen(fil, "r")) == NULL) {
		printf("\nFile not found");		
		close(s);
		close(ns);
		exit(0);
		}
		while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			find_result++;
		}
		row++;
		}
		if(fp) {
		fclose(fp);
		}
		buff[0]=find_result;
		sntb=send(ns,buff,sizeof(buff),0);
		if(sntb==-1)
		{
		printf("\nMessage Sending Failed");
		close(s);
		close(ns);
		exit(0);
		}
		break;

		case 2:
		n1=buff[1];
		i=2;
		for(j=0;j<n1;j++)
		{
			str1[j]=buff[i];
			i++;
		}
		str1[j]='\0';
		recb=recv(ns,buff,sizeof(buff),0);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		close(ns);
		exit(0);
	}	
		n=buff[1];
		i=2;
		for(j=0;j<n;j++)
		{
			str2[j]=buff[i];
			i++;
		}
		str2[j]='\0';
		printf("\nReplacing %s with %s..\n",str1,str2);
		FILE * fptr;
    	FILE * ft;
    	char buffer[1000];
    	fptr  = fopen(fil, "r");
    	ft = fopen("replace.tmp", "w"); 
    	if (fptr == NULL || ft == NULL)
   		 {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(0);
    	}
    	 while ((fgets(buffer, 1000, fptr)) != NULL)
    	{
        // Replace all occurrence of word from current line
        replaceAll(buffer, str1, str2);

        // After replacing write it to temp file.
        fputs(buffer, ft);
    	}


    /* Close all files to release resource */
    	fclose(fptr);
    	fclose(ft);


    /* Delete original source file */
    	remove(fil);

    /* Rename temp file as original file */
    	rename("replace.tmp", fil);
    	strcpy(buff,"Replace finished!");
    	sntb=send(ns,buff,sizeof(buff),0);
		break;
		case 3:printf("\nOrdering file..\n");
		
    FILE * plog = NULL;
    FILE * ps = NULL;

    if ( (plog = fopen(fil, "r")) == NULL ) {
        fprintf(stderr,"Error: Could not open %s\n",fil);
        return 1;
    }
    if ( (ps = fopen("temp.txt", "a")) == NULL ) {
        fprintf(stderr,"Error: Could not open temp.txt\n");
        return 1;
    }

    while(fgets(temp, MAX_LEN, plog) != NULL) {
        if(strchr(temp,'\n'))
            temp[strlen(temp)-1] = '\0';
        arr = (char**)realloc(arr, sizeof(char**)*(rows+1));
        arr[rows] = (char*)calloc(MAX_LEN,sizeof(char));
        strcpy(arr[rows], temp);
        rows++;
    }
    for(i= 0; i < (rows - 1); ++i) {
        for(j = 0; j < ( rows - i - 1); ++j) {
            if(strcmp(arr[j], arr[j+1]) > 0) {
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j+1]);
                strcpy(arr[j+1], temp);
            }
        }
    }
    for(i = 0; i < rows; i++)
        fprintf(ps,"%s\n",arr[i]);
    for(i = 0; i < rows; i++)
        free(arr[i]);
    free(arr);
    remove(fil);
    rename("temp.txt",fil);
    fclose(plog);
    fclose(ps);
		strcpy(buff,"Ordering done!");
		sntb=send(ns,buff,sizeof(buff),0);
		if(sntb==-1)
		{
		printf("\nMessage Sending Failed");
		close(s);
		close(ns);
		exit(0);
		}
		break;

		case 4: ch=4;
		break;
	}
}
	close(ns);
	close(s);
}