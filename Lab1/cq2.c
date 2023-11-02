// Q2 client
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#define myport 1324

int main()
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(myport);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));
	printf("Successful till here");
	
	char buffer[20];
	int size = sizeof(struct sockaddr);
	char result[20];
	int len;
	int a=0, e=0, i=0, o=0, u=0;
	while(1)
	{
		printf("\nEnter the string:");
		printf("\n");
		scanf("%s", buffer);
		if(strcmp(buffer, "Halt")==0)
		{
			sendto(sockfd, buffer, 20,0, (struct sockaddr *)& addr, size);		
			printf("Closing the socket(client)");	
			close(sockfd);
			exit(0);
		}
		sendto(sockfd, buffer, sizeof(buffer),0, (struct sockaddr *)& addr, size);
		recvfrom(sockfd, result, sizeof(result), 0, (struct sockaddr *)& addr, &size);
		recvfrom(sockfd, &len, 4, 0, (struct sockaddr *)& addr, &size);		
		recvfrom(sockfd, &a, sizeof(a),0, (struct sockaddr *)& addr, &size);	
		recvfrom(sockfd, &e, sizeof(e),0, (struct sockaddr *)& addr, &size);	
		recvfrom(sockfd, &i, sizeof(i),0, (struct sockaddr *)& addr, &size);	
		recvfrom(sockfd, &o, sizeof(o),0, (struct sockaddr *)& addr, &size);	
		recvfrom(sockfd, &u, sizeof(u),0, (struct sockaddr *)& addr, &size);	
		printf("Size of the string = %d\n", len);
		printf("%s\n",result);
		printf("Vowels count:\n");
		printf("A = %d\n", a);
		printf("E = %d\n", e);
		printf("I = %d\n", i);
		printf("O = %d\n", o);
		printf("U = %d\n", u);
	}
	return 0;
}
