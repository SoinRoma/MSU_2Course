#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
int main(void)
{
        pid_t getpid(void);
        pid_t getppid(void);
        int  a=getpid();
        int  b=getppid();
        printf("%d\n%d\n",a,b);
        return 0;
}
