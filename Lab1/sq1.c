#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90
void main(){
	int sockfd,newsockfd,retval;
	socklen_t actuallen;
	int rb1,rb2,rb3,sb;
	struct sockaddr_in serveraddr,clientaddr;

	int buff[MAXSIZE];
	int a=0;
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	if(sockfd==-1){
		printf("\nSocket creation error");
	}

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
	retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==1){
		printf("Binding error");
		close(sockfd);
	}

	retval=listen(sockfd,1);
	if(retval==-1){
		close(sockfd);
	}
	actuallen=sizeof(clientaddr);
	newsockfd=accept(sockfd,(struct sockaddr*)&clientaddr,&actuallen);
	if(newsockfd==-1){
		close(sockfd);
	}
	printf("Connected\n");
	int n,ch;
	while(1){
	recv(newsockfd,buff,sizeof(buff),0);
	recv(newsockfd,&n,sizeof(n),0);
	recv(newsockfd,&ch,sizeof(ch),0);
	if(ch==1){
		int ele;
		recv(newsockfd,&ele,sizeof(ele),0);
		int flag=0;
		for(int i=0;i<n;i++){
			if(buff[i]==ele){
				flag=1;
				printf("\nFound\n");
			}
		}
		if(!flag){
			printf("\nNot Found\n");
		}
	}
	else if(ch==2){
		int ch2;
		recv(newsockfd,&ch2,sizeof(ch2),0);
		for(int i=0;i<n-1;i++){
			for(int j=0;j<n-i-1;j++){
				if(buff[j]>buff[j+1]){
					int temp=buff[j];
					buff[j]=buff[j+1];
					buff[j+1]=temp;
				}
			}
		}
		if(ch2!=1){
			for(int i=0,j=n-1;i<n/2;i++,j--){
				int temp=buff[i];
				buff[i]=buff[j];
				buff[j]=temp;
			}
		}
		printf("SORTED ARRAY: ");
		for(int i=0;i<n;i++){
			printf("%d ",buff[i]);
		}
		printf("\n");
	}
	else if(ch==3){
		printf("\nEVEN VALUES: ");
		for(int i=0;i<n;i++){
			if(buff[i]%2==0){
				printf("%d ",buff[i]);
			}
		}
		printf("\nODD VALUES: ");
		for(int i=0;i<n;i++){
			if(buff[i]%2==1){
				printf("%d ",buff[i]);
			}
		}
		printf("\n");
	}
	else{
		printf("EXITING...");
		break;
	}
	}
	close(sockfd);
	close(newsockfd);
}