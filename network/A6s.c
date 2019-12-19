#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main ()
{
    char msg[1024];

    int sockfd= socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in groupaddr = { AF_INET, htons(1236), inet_addr("226.1.1.1") };

    struct in_addr localInterface = { INADDR_ANY }; /* Internet address. */
    setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface));
    //IPPROTO_IP = 0,    /* Dummy protocol for TCP.  */#define IPPROTO_IP      IPPROTO_IP Set the local device for a multicast socket.
    
    printf("Enter message : ");
    fgets(msg, 1024, stdin);
    msg[strlen(msg)-1] = '\0'; // to remove '\n' from string

    sendto(sockfd, msg, sizeof(msg), 0, (struct sockaddr*)&groupaddr, sizeof(groupaddr));
    
    printf("Message Sent.\n");
            
    return 0;
}
/*

shree@dell-Inspiron-5559:~/network$ gcc A7s.c
shree@dell-Inspiron-5559:~/network$ ./a.out
Enter message : work is worship
Message Sent.
shree@dell-Inspiron-5559:~/network$ 
*/
