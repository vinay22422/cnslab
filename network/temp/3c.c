#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()

{
    char b[1000],fna[50];
    int n,sock=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in a={AF_INET,htons(1212),inet_addr("127.0.0.1")};
    while(connect(sock,(struct sockaddr*)&a,sizeof(a)));
    printf("\nconnected\n");

    gets(fna);
    send(sock,fna,50,0);

    while((n=recv(sock,b,1000,0))>0)
        printf("%s",b);
        /*



    recv(s,fna,50,0);
    fd=open(fna,O_RDONLY);
    if(!fd)
    {
        send(s,"\n\nno file\n\n",12,0);
    }
    else{
        while((n=read(fd,b,1000))>0)
            send(s,b,n,0);
    }


*/


}
