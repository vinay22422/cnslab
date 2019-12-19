#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <arpa/inet.h> 

int main()
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addr = { AF_INET, htons(1236), INADDR_ANY };
	bind(sock, (struct sockaddr*)&addr, sizeof(addr));
	char buffer[100];
	char *msg = "this is server";	
	int len = sizeof(addr);	
	recvfrom(sock, buffer, sizeof(buffer), 0, ( struct sockaddr *) &addr, &len); 
	printf("%s\n", buffer);
	sendto(sock, msg, strlen(msg), 0, (struct sockaddr *) &addr,sizeof(addr));
	return 0;
}
/* OUTPUT

shree@dell-Inspiron-5559:~/network$ gcc A5s.c
shree@dell-Inspiron-5559:~/network$ ./a.out
Waiting for message from client...
Client : hi
Server : hello
Client : bye
Server : see you

*/
