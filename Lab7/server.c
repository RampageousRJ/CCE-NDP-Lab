#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#define MAXSIZE 90

struct user
{
    char *username;
    char *password;
    char *amount;
};

char epass[MAXSIZE];
void encrypt(char *pass)
{
    int len = strlen(pass);
    for (int i = 0; i < len; i++)
    {
        if (pass[i] >= 48 && pass[i] <= 57)
        {
            int val = 48 + ((pass[i] - 48) + 3) % 10;
            pass[i] = (char)val;
        }
        else if (pass[i] >= 97 && pass[i] <= 122)
        {
            int val = 97 + ((pass[i] - 97) + 3) % 26;
            pass[i] = (char)val;
        }
        else
        {
            int val = 65 + ((pass[i] - 65) + 3) % 26;
            pass[i] = (char)val;
        }
    }
    strcpy(epass, pass);
}

int checkCredentials(char *username, char *password)
{
    char buff[256];
    int count = 0;
    FILE *fp = fopen("users.txt", "r");
    int flag = 0;
    struct user arr[MAXSIZE];
    while (fscanf(fp, "%s", buff) != EOF)
    {
        if (flag)
        {
            if (strcmp(buff, password) == 0)
            {
                return 1;
            }
            else
            {

                return 0;
            }
        }
        if (flag == 0)
        {
            flag = 1;
        }
    }
    return 0;
}

int checkBalance(char *username)
{
    char buff[256];
    int count = 0;
    FILE *fp = fopen("users.txt", "r");
    FILE *fp1 = fopen("temp.txt", "w");
    FILE *fp2 = fopen("users.txt", "w");
    int flag = 0;
    while (fscanf(fp, "%s", buff) != EOF)
    {
        if (!flag)
        {
            if (strcmp(username, buff) == 0)
            {
                flag++;
            }
        }
        else if (flag == 1)
        {
            flag++;
        }
        else
        {
            return atoi(buff);
        }
    }
    fclose(fp);
    return 0;
}

void debit(char *username, int amount)
{
}

void withdraw(char *username, int amount)
{
}

void main()
{
    int s, ns, retval;
    socklen_t actuallen;
    struct sockaddr_in serveraddr, clientaddr;
    struct user arr[MAXSIZE];
    FILE *fp = fopen("users.txt", "r");
    int flag = 0;
    char *buff;
    int n = 0;
    while (fscanf(fp, "%s", buff) != EOF)
    {
        if (!flag)
        {
            strcpy(arr[n].username, buff);
            flag++;
        }
        else if (flag == 1)
        {
            strcpy(arr[n].password, buff);
            flag++;
        }
        else
        {
            strcpy(arr[n++].amount, buff);
            flag = 0;
        }
    }
    fclose(fp);
    char username[MAXSIZE];
    char password[MAXSIZE];
    char status[MAXSIZE];
    int a = 0;
    s = socket(AF_INET, SOCK_STREAM, 0);

    if (s == -1)
    {
        printf("\nSocket creation error");
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3300);
    serveraddr.sin_addr.s_addr = htons(INADDR_ANY);
    retval = bind(s, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (retval == 1)
    {
        printf("Binding error");
        close(s);
    }

    retval = listen(s, 1);
    if (retval == -1)
    {
        close(s);
    }
    actuallen = sizeof(clientaddr);
    ns = accept(s, (struct sockaddr *)&clientaddr, &actuallen);
    if (ns == -1)
    {
        close(s);
    }
    printf("Connected\n");
    int ch = 1;
    char login = 'n';
    while (1)
    {
        if (login == 'n')
        {
            recv(ns, username, sizeof(username), 0);
            recv(ns, password, sizeof(password), 0);
            encrypt(password);
            if (checkCredentials(username, epass))
            {
                strcpy(status, "ok");
            }
            else
            {
                strcpy(status, "retry");
            }
            send(ns, status, sizeof(status), 0);
            recv(ns, status, sizeof(status), 0);
            if (strcmp(status, "retry") == 0)
            {
                printf("\nRetrying...");
                continue;
            }
            login = 'y';
        }
        else
        {
            int bal;
            recv(ns, &ch, sizeof(ch), 0);
            printf("\n%d\n", ch);
            if (ch == 1)
            {
                recv(ns, &bal, sizeof(bal), 0);
                debit(username, bal);
            }
            else if (ch == 2)
            {
                recv(ns, &bal, sizeof(bal), 0);
                withdraw(username, bal);
            }
            else if (ch == 3)
            {
                int bal = checkBalance(username);
                send(ns, &bal, sizeof(bal), 0);
            }
            else
            {
                printf("EXITING...");
                break;
            }
        }
    }
    close(s);
    close(ns);
}