#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define MAXSIZE 90

void main()
{
    int sockfd, retval;
    int recedbytes, sentbytes1, sentbytes2, sentbytes3;
    struct sockaddr_in serveraddr;
    char username[MAXSIZE];
    char password[MAXSIZE];
    char status[MAXSIZE];
    char login = 'n';
    int buff[MAXSIZE];
    int ch;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("\nSocket Creation Error");
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3300);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    retval = connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (retval == -1)
    {
        printf("Connection error");
    }

    while (1)
    {
        if (login == 'n')
        {
            printf("\nEnter username: ");
            gets(username);
            printf("\nEnter password: ");
            gets(password);

            send(sockfd, username, sizeof(username), 0);
            send(sockfd, password, sizeof(password), 0);
            recv(sockfd, status, sizeof(status), 0);
            if (strcmp(status, "ok") == 0)
            {
                login = 'y';
                printf("\nCorrect Username");
            }
            else
            {
                strcpy(status, "retry");
                printf("\nIncorrect Username");
            }
            send(sockfd, status, sizeof(status), 0);
        }
        else
        {
            login = 'y';
            printf("\n\nMENU\n1.Debit\n2.Credit\n3.View Balance\n4.Exit\nEnter the choice: ");
            scanf("%d", &ch);
            send(sockfd, &ch, sizeof(ch), 0);
            if (ch == 1)
            {
                int amount;
                printf("Enter amount to deposit: ");
                scanf("%d", &amount);
                send(sockfd, &amount, sizeof(amount), 0);
                printf("\nDeposited %d amount successfully...", amount);
            }
            else if (ch == 2)
            {
                int amount;
                printf("Enter amount to withdraw: ");
                scanf("%d", &amount);
                send(sockfd, &amount, sizeof(amount), 0);
                printf("\nWithdrew %d amount successfully...", amount);
            }
            else if (ch == 3)
            {
                int bal = 0;
                recv(sockfd, &bal, sizeof(bal), 0);
                printf("\nCurrent Balance: %d", bal);
            }
            else if (ch == 4)
            {
                printf("EXITING...");
                break;
            }
            else
            {
                printf("Invalid Option...");
            }
        }
    }

    close(sockfd);
}