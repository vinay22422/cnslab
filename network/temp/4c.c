#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include<string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>

int main()

{
    char b[1000],fna[50];
    int n,s,fd1,fd2,fd3;

   gets(fna);


    fd1=open("req.fifo",O_WRONLY);
    fd2=open("res.fifo",O_RDONLY);

    write(fd1,fna,50);



    read(fd1,fna,50);

    while((n=read(fd2,b,1000))>0)
        printf("%s",b);









}
