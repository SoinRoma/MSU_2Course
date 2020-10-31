#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int fd[2];
    long int result;
    unsigned long long int size;
    char string[] = "1";
    char resstring[14];
if(pipe(fd)<0)
    {
        
        printf("Can1\'t create pipe\n");
        exit(-1);
    }
else
{
    while(write(fd[1], "1", 1)>0)
{
size++;

printf("%lld\n", size);
}
}
return 0;
}
