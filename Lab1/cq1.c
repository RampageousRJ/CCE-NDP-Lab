#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 90

void main()
{
	int sockfd,retval;
	int recedbytes,sentbytes1,sentbytes2,sentbytes3;
	struct sockaddr_in serveraddr;

	int buff[MAXSIZE];
	int n;
	printf("Enter number of items: ");
	scanf("%d",&n);
	printf("\nEnter array: ");
	for(int i=0;i<n;i++){
		scanf("%d",&buff[i]);
	}
	printf("\nArray: ");
	for(int i=0;i<n;i++){
		printf("%d ",buff[i]);
	}
	printf("\n\n");

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		printf("\nSocket Creation Error");
	}
	// printf("%i",sockfd);
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

	if(retval==-1){
		printf("Connection error");
	}
	int ch;
	while(1){
	printf("\n\nMENU\n1.Search\n2.Sort\n3.Split\n4.Exit\nEnter the choice: ");
	scanf("%d",&ch);
	printf("\n");
	send(sockfd,buff,sizeof(buff),0);
	send(sockfd,&n,sizeof(n),0);
	send(sockfd,&ch,sizeof(ch),0);
	if(ch==1){
		int ele;
		printf("Enter element to search: ");
		scanf("%d",&ele);
		send(sockfd,&ele,sizeof(ele),0);
	}
	else if(ch==2){
		int ch2;
		printf("Ascending(1) or Descending(2): ");
		scanf("%d",&ch2);
		send(sockfd,&ch2,sizeof(ch2),0);
		printf("\n");
	}
	else if(ch==3){
		continue;
	}
	else{
		break;
	}
	
	}
	

	close(sockfd);
}