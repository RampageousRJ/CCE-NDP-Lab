#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#define MAX_LEN 100
void replaceAll(char *str, const char *str1, const char *str2)
{
    char *pos, temp[1000];
    int index = 0;
    int owlen;

    owlen = strlen(str1);
    while ((pos = strstr(str, str1)) != NULL)
    {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, str2);
        strcat(str, temp + index + owlen);
    }
}
int main()
{
	int s,r,recb,sntb,x;
	int ca;
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50];

	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	len=sizeof(client);
	ca=sizeof(client);

	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
		{
		printf("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded.");

	recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		exit(0);
	}	
	
	printf("\nFile Name Recieved!\n");
	char fil[50];
	if( access( buff, F_OK ) != -1 ) {
    // file exists
		strcpy(fil,buff);
		strcpy(buff,"File exists");
	} else {
    // file doesn't exist
		strcpy(buff,"File does not exist!");
	}

	sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		exit(0);
	}
	if(strcmp(buff,"File does not exist!")==0)
	{
		close(s);
		//close(ns);
		exit(0);
	}
	int ch=0;
	while(ch!=4){
		recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		exit(0);
	}	
	ch = buff[0];
	int i,n,n1,n2,j;
	char str[50],str1[50],str2[50];
	char stemp[MAX_LEN];
    char **arr = NULL; // String List
    int lines = 0;
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
		int res = 0;
		char temp[512];
		if((fp = fopen(fil, "r")) == NULL) {
		printf("\nFile not found");		
		close(s);
		//close(ns);
		exit(0);
		}
		while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			res++;
		}
		row++;
		}
		if(fp) {
		fclose(fp);
		}
		buff[0]=res;
		sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
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
	recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
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
    	sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		exit(0);
	}
		break;
	case 3:	printf("\nOrdering file..\n");
		
    FILE * plog = NULL;
    FILE * psum = NULL;

    if ( (plog = fopen(fil, "r")) == NULL ) {
        fprintf(stderr,"Error: Could not open %s\n",fil);
        return 1;
    }
    if ( (psum = fopen("temp.txt", "a")) == NULL ) {
        fprintf(stderr,"Error: Could not open temp.txt\n");
        return 1;
    }

    // Read and store in a string list.
    while(fgets(stemp, MAX_LEN, plog) != NULL) {
        // Remove the trailing newline character
        if(strchr(stemp,'\n'))
            stemp[strlen(stemp)-1] = '\0';
        arr = (char**)realloc(arr, sizeof(char**)*(lines+1));
        arr[lines] = (char*)calloc(MAX_LEN,sizeof(char));
        strcpy(arr[lines], stemp);
        lines++;
    }
    // Sort the array.
    for(i= 0; i < (lines - 1); ++i) {
        for(j = 0; j < ( lines - i - 1); ++j) {
            if(strcmp(arr[j], arr[j+1]) > 0) {
                strcpy(stemp, arr[j]);
                strcpy(arr[j], arr[j+1]);
                strcpy(arr[j+1], stemp);
            }
        }
    }
    // Write it to outfile. file.
    for(i = 0; i < lines; i++)
        fprintf(psum,"%s\n",arr[i]);
    // free each string
    for(i = 0; i < lines; i++)
        free(arr[i]);
    // free string list.
    free(arr);
    remove(fil);
    rename("temp.txt",fil);
    fclose(plog);
    fclose(psum);
		strcpy(buff,"Ordering done!");
		sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		exit(0);
	}
		break;

		case 4: ch=4;
		break;

	}
	}
	close(s);
}