#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>

int main()

{
    char b[1000],fna[50];
    int n,s,fd1,fd2,fd3;

    mkfifo("req.fifo",0777);
    mkfifo("res.fifo",0777);

    fd1=open("req.fifo",O_RDONLY);
    fd2=open("res.fifo",O_WRONLY);

    read(fd1,fna,50);

    fd3=open(fna,O_RDONLY);

    if(fd3<0){
    printf("no file");exit(0);
    }

    while((n=read(fd3,b,1000))>0)
        write(fd2,b,1000);











}
