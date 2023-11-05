#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#define MAXSIZE 90

void main()
{
    int s, ns, retval;
    socklen_t actuallen;
    int recedbytes1, recedbytes2, recedbytes3, sentbytes;
    struct sockaddr_in serveraddr, clientaddr;

    char buff[MAXSIZE];
    char nbuff[MAXSIZE];
    char abuff[MAXSIZE];

    int a = 0;
    s = socket(AF_INET, SOCK_STREAM, 0);

    if (s == -1)
    {
        printf("\nSocket creation error");
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3390);
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
        printf("New Socket Cannot Be Made...");
        close(s);
    }
    printf("Connected\n");
    int n;
        recv(ns, buff, sizeof(buff), 0);
        recv(ns, &n, sizeof(n), 0);
        printf("\nRecieved: %s\n", buff);
        int pid = fork();
        if (pid == 0)
        {
            int i = 0;
            for (int j = 0; j < n; j++)
            {
                if (buff[j] > 47 && buff[j] < 58)
                {
                    nbuff[i++] = buff[j];
                }
            }
            int m = i;
            i = 0;
            for (i = 0; i < m - 1; i++)
            {
                for (int j = 0; j < m - i - 1; j++)
                {
                    if (nbuff[j] > nbuff[j + 1])
                    {
                        int temp = nbuff[j];
                        nbuff[j] = nbuff[j + 1];
                        nbuff[j + 1] = temp;
                    }
                }
            }
            send(ns, nbuff, sizeof(nbuff), 0);
        }
        else if (pid > 0)
        {
            strcpy(abuff, "");
            int i = 0;
            for (int j = 0; j < n; j++)
            {
                if (buff[j] > 64)
                {
                    abuff[i++] = buff[j];
                }
            }
            int m = i;
            i = 0;
            for (i = 0; i < m - 1; i++)
            {
                for (int j = i + 1; j < m; j++)
                {
                    if (abuff[j] < abuff[i])
                    {
                        char temp = abuff[i];
                        abuff[i] = abuff[j];
                        abuff[j] = temp;
                    }
                }
            }
            for(int i=0,j=m-1;i<m/2;i++,j--){
                char temp = abuff[i];
                abuff[i] = abuff[j];
                abuff[j] = temp;
            }
            send(ns, abuff, sizeof(abuff), 0);
        }
        else
        {
            printf("ERROR");
        }
    close(s);
    close(ns);
}