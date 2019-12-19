#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h>

#include <sys/stat.h>//optional
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
int main()
{
	int r=1,sock=socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addr = { AF_INET, htons(1236), INADDR_ANY };


	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char *)&r,sizeof(r));
	bind(sock,(struct sockaddr*)&addr,sizeof(addr));


	struct ip_mreq grp={inet_addr("226.1.1.1"), INADDR_ANY};

	setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char *)&grp,sizeof(grp));



	char buffer[1000];

	printf("Waiting for message from server.....");

	read(sock,buffer,1000);
	printf("%s",buffer);

	printf("\nThe message from multicast server is \n");

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
