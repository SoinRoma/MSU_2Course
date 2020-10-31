#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
int main(int argc, char *argv[], char *envp[])
{
 pid_t pid, ppid;
int a=0, i=0;
a=a+1;
pid=getpid();

printf("p=%d,pp=%d, a=%d", (int)pid, (int)ppid,a);
for(i=0;i<argc;i++)
printf("%s",argv[i]);
        return 0;
}
