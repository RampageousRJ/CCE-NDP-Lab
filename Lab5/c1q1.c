#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<netdb.h>
#include<errno.h>
int main()
{
	int s,r,recb,sntb,x;
	struct sockaddr_in server;
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
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	r=connect(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nConnection error.");
		exit(0);
	}
	printf("\nSocket connected.");

	strcpy(buff,"Institute Of");

	sntb=send(s,buff,sizeof(buff),0);
	if(sntb==-1)
	{
		close(s);
		printf("\nMessage Sending Failed");
		exit(0);
	}

	struct hostent *host_entry;
	int hname;
	char hbuffer[256];
	char *ipbuff;
	hname=gethostname(hbuffer,sizeof(hbuffer));
	host_entry=gethostbyname(hbuffer);
	ipbuff = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));
	char ip[50];
	strcpy(ip,ipbuff);
	strcat(ip,"    ");
	printf("\nIP is: %s",ip);
	sntb=send(s,ip,sizeof(ip),0);
	if(sntb==-1)
	{
		close(s);
		printf("\nMessage Sending Failed");
		exit(0);
	}
	close(s);

}
