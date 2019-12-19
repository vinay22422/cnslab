#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

#include <sys/stat.h>//optional
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
	int sock=socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in gaddr = { AF_INET, htons(1236), inet_addr("226.1.1.1") };

	struct in_addr locali={INADDR_ANY};

	setsockopt(sock,IPPROTO_IP,IP_MULTICAST_IF,(char *)&locali,sizeof(locali));



	char buffer[100];

	//char *msg = "This is servers multicast message \n recived by multi consoles together at a time\n  ";
	char msg[1024];
	strcpy(msg,"This is servers multicast message \n recived by multi consoles together at a time\n ");
	 msg[strlen(msg)-2] = '\0';

	sendto(sock, msg, strlen(msg), 0, (struct sockaddr *) &gaddr,sizeof(gaddr));

	/*printf("Enter message : ");
    fgets(msg, 1024, stdin);
    msg[strlen(msg)-1] = '\0'; // to remove '\n' from string

    sendto(sock, msg, sizeof(msg), 0, (struct sockaddr*)&gaddr, sizeof(gaddr));
    */
    printf("Message Sent.\n");
	close(sock);
	return 0;
}
/*

shree@dell-Inspiron-5559:~/network$ gcc A5c.c
shree@dell-Inspiron-5559:~/network$ ./a.out
Client : hi
Server : hello
Client : bye
Server : see you
Client :
*/
