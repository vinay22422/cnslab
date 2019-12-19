#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    char fname[50], buffer[1025];
    int req, res, n;

    req = open("req.fifo", O_WRONLY);
    res = open("res.fifo", O_RDONLY);

    if(req < 0 || res < 0)
    {
        printf("Please Start the server first\n");
        exit(-1);
    }

    printf("Enter filename to request : ");
    scanf("%s", fname);

    // write file name to request file
    write(req, fname, sizeof(fname));

    printf("Received response\n");
    printf("-------------------------------------------\n");
    while((n = read(res, buffer, sizeof(buffer)))>0)
    {
        printf("%s", buffer);
    }
    printf("-------------------------------------------\n");
    
    close(req);
    close(res);
    
    return 0;
}

/* output

shree@dell-Inspiron-5559:~/network$ gcc A6c.c
shree@dell-Inspiron-5559:~/network$ ./a.out
Enter filename to request : file.txt
Received response
-------------------------------------------
Multinational companies (MNCs) had to increase their global activity by inventing new management policies and practices. That led to the internationalization of HRM. Firms had to implement global strategies in their subsidiaries, to promote the maximization of economic goals.
-------------------------------------------
shree@dell-Inspiron-5559:~/network$ 
*/
