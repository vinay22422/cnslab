#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> /*used for file handling*/
#include <sys/stat.h> /*used for mkfifo function*/
#include <sys/types.h> /*when compiled in gcc, mkfifo() has dependency on both types.h and stat.h*/

int main()
{
    char fname[50], buffer[1025];
    int req, res, n, fd;
    
    mkfifo("req.fifo", 0777);
    mkfifo("res.fifo", 0777);
    
    printf("Waiting for request...\n");
    req = open("req.fifo", O_RDONLY);
    res = open("res.fifo", O_WRONLY);
    
    read(req, fname, sizeof(fname));
    printf("Received request for %s\n", fname);
    
    fd = open(fname, O_RDONLY);
    if (fd < 0)
    {
        write(res, "fd not found\n", 15);
    }
    else
    {
        while((n = read(fd, buffer, sizeof(buffer))) > 0)
        {
            write(res, buffer, n);
        }
    }
    
    close(req);
    close(res);
    
    unlink("req.fifo");
    unlink("res.fifo");
    
    return 0;
}
/*
shree@dell-Inspiron-5559:~/network$ gcc A6s.c
shree@dell-Inspiron-5559:~/network$ ./a.out
Waiting for request...
Received request for fd.txt
shree@dell-Inspiron-5559:~/network$ 
*/
