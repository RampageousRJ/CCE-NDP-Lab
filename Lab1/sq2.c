//q2 accept a string from user, send it to server and check if it a palindrome. then return length of the string along with the count of each vowels in the string

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#define myport 1324

// udp - create bind nolisten noaccept send and receive
int main()
{

	
	int sockfd;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in server_addr, client_addr;
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(myport);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //this has to do something with the localhost
	memset( &(server_addr.sin_zero), '\0', sizeof(server_addr.sin_zero));
	
	bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	
	printf("Waiting to recieve...");
	printf("\n");
	
	char buffer[20];
	int size = sizeof(struct sockaddr);
	int len=0, i, j;
	
	//recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &client_addr, &size);
	//printf("%s", buffer);
	while(1)
	{
	
		recvfrom(sockfd, buffer, 20, 0, (struct sockaddr*)& client_addr, &size);
		printf("\nRecieved: ");
		puts(buffer);
		if(strcmp(buffer, "Halt")==0)
		{
			close(sockfd);
			exit(0);
		} 
		len = strlen(buffer);
		char revbuf[20];
		int a=0, e=0, I=0, o=0, u=0;
		for(i=0, j=len-1 ; j>=0 ; j--, i++)
		{	revbuf[i] = buffer[j];
			switch(buffer[i])
			{
				case 'a':
				case 'A': a++; break;
				
				case 'e':
				case 'E': e++; break;
				
				case 'i':
				case 'I': I++; break;
				
				case 'o':
				case 'O': o++; break;
				
				case 'u':
				case 'U': u++; break;				
			}
		}
		revbuf[i] = '\0'; // palindrome wont work without this
		char result[20];
		if(strcmp(revbuf, buffer)==0)
			strcpy(result, "Palindrome");
		else
			strcpy(result , "Not a palindrome");

		sendto(sockfd, result, sizeof(result), 0, (struct sockaddr*)& client_addr, size);
		sendto(sockfd, &len, sizeof(len), 0, (struct sockaddr*)& client_addr, size);
		sendto(sockfd, &a, sizeof(a), 0, (struct sockaddr *)& client_addr, size);	
		sendto(sockfd, &e, sizeof(e), 0, (struct sockaddr *)& client_addr, size);	
		sendto(sockfd, &I, sizeof(I), 0, (struct sockaddr *)& client_addr, size);	
		sendto(sockfd, &o, sizeof(o), 0, (struct sockaddr *)& client_addr, size);	
		sendto(sockfd, &u, sizeof(u), 0, (struct sockaddr *)& client_addr, size);	
	}	
	close(sockfd);	
	return 0;
}
