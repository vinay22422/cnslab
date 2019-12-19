#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()

{
    char b[1000],fna[50];
    int n,s,fd,sock=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in a={AF_INET,htons(1212),INADDR_ANY};
    bind(sock,(struct sockaddr *)&a,sizeof(a));
    listen(sock,15);
    s=accept(sock,NULL,NULL);

    recv(s,fna,50,0);
    printf("\n%s\n",fna);
    fd=open(fna,O_RDONLY);
    if(fd<0)
    {
        char *c="\n\nno file\n\n";
        send(s,c,12,0);
    }
    else{
        while((n=read(fd,b,1000))>0)
            send(s,b,n,0);
    }





}
