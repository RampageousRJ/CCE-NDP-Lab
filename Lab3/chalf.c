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

int main() {
  int sockfd, retval, recb, sntb, x;
  socklen_t len;
  struct sockaddr_in server, client;
  char buff[50];
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1) {
    printf("\nSocket creation error.");
    exit(0);
  }
  server.sin_family = AF_INET;
  server.sin_port = htons(3388);
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  len = sizeof(server);
  while(1) {
    printf("\n\n");
    printf("Type Message (enter 'stop' to exit): ");
    scanf("%s", buff);
    sntb = sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr * ) & server, len);
    if (sntb == -1) {
      close(sockfd);
      printf("\nMessage sending Failed");
      exit(0);
    }
    if (!strcmp(buff, "stop"))
      break;
  }
  close(sockfd);
}