#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

void swap(char * x, char * y) {
  char temp;
  temp = * x;
  * x = * y;
  * y = temp;
}

void permute(char * str, int curr, int target) {
  int i;
  if (curr == target)
    printf("%s \n", str);
  else 
  {
    for (i = curr; i <= target; i++) 
    {
      swap((str + curr), (str + i));
      permute(str, curr + 1, target);
      swap((str + curr), (str + i));
    }
  }
}

int main() 
{
  int sockfd, retval, recb, sntb, x;
  int ca;
  socklen_t len;
  struct sockaddr_in server, client;
  char buff[50];
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1) 
  {
    printf("\nSocket creation error.");
    exit(0);
  }
  server.sin_family = AF_INET;
  server.sin_port = htons(3388);
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  len = sizeof(client);
  ca = sizeof(client);
  retval = bind(sockfd, (struct sockaddr * ) & server, sizeof(server));
  if (retval == -1) 
  {
    printf("\nBinding error.");
    exit(0);
  }
  while (1) 
  {
    recb = recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr * ) & client, & len);
    if (recb == -1) 
    {
      printf("\nMessage Recieving Failed");
      close(sockfd);
      exit(0);
    }
    printf("\nMessage Recieved: ");
    printf("%s", buff);
    if (!strcmp(buff, "stop"))
      break;
    printf("\nPermutations of the string are: \n");
    int n = strlen(buff);
    permute(buff, 0, n - 1);
  }
  close(sockfd);
}