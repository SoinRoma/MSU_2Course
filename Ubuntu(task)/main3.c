#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
int main(void)
{
        pid_t a=fork();
        printf("%d\n",a);
        return 0;
}
