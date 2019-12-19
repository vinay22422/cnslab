#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <arpa/inet.h> 

int main()
{
	int sock=socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addr = { AF_INET, htons(1236), INADDR_ANY };
	connect(sock, (struct sockaddr*)& addr, sizeof(addr));
	
	char buffer[100];
	char *msg = "This is client";
	
	sendto(sock, msg, strlen(msg), 0, (struct sockaddr *) &addr,sizeof(addr));
	int len = sizeof(addr);
	recvfrom(sock, buffer, sizeof(buffer), 0, ( struct sockaddr *) &addr, &len); 
	printf("%s\n", buffer);
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
