#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
	int  reuse = 1;
	char msg[1024];
/* Internet address. */
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addr = { AF_INET, htons(1236), INADDR_ANY };
	
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));//SOL_SOCKET is the socket layer itself. It is used for options that are protocol independent
	//suppose we want to set the socket option to reuse the address to 1 (on/true), we pass in the "level" SOL_SOCKET and the value we want it set to.
	bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));


	struct ip_mreq group = { inet_addr("226.1.1.1"), INADDR_ANY };	
	//Join a multicast group.  Argument is an ip_mreqn structure conaintning IP multicast group address IP address of local interface
	setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group));
	//								i am	
	printf("Waiting for message from server.....");

	read(sockfd, msg, sizeof(msg));

	printf("\nThe message from multicast server is : %s \n", msg);
	close(sockfd);
	return 0;
}

/*
(in multiple window)

shree@dell-Inspiron-5559:~/network$ gcc A7c.c
shree@dell-Inspiron-5559:~/network$ ./a.out
Waiting for message from server.....
The message from multicast server is : work is worship 
shree@dell-Inspiron-5559:~/network$ 
*/




