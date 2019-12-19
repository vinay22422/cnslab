#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sock, n;
    char buffer[1024], fname[50];

    /* sockfd = socket(domain, type, protocol) */ 
    sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = { AF_INET, htons(1234), inet_addr("127.0.0.1") };

    /*  keep trying to esatablish connection with server */
    while(connect(sock, (struct sockaddr *) &addr, sizeof(addr))) ;
    printf("\nClient is connected to Server");

    /* send the filename to the server */
    printf("\nEnter file name: ");
    scanf("%s", fname);
    send(sock, fname, sizeof(fname), 0);

    printf("\nRecieved file data\n");
    printf("---------------------------------------------------------\n");

    /*  keep printing any data received from the server */
    while ((n = recv(sock, buffer, sizeof(buffer), 0)) > 0)
    {
	buffer[n] = '\0' ;
        printf("%s", buffer);
    }
    printf("---------------------------------------------------------\n");
	
    return 0;
}

/*
shree@dell-Inspiron-5559:~/network$ gcc A4c.c
shree@dell-Inspiron-5559:~/network$ ./a.out

Client is connected to Server
Enter file name: file.txt

Recieved file data
---------------------------------------------------------
Multinational companies (MNCs) had to increase their global activity by inventing new management policies and practices. That led to the internationalization of HRM. Firms had to implement global strategies in their subsidiaries, to promote the maximization of economic goals.
---------------------------------------------------------
shree@dell-Inspiron-5559:~/network$ 
*/
