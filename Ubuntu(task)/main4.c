#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
int main(void)
{
  pid_t pid, ppid;
  pid_t fpid =fork();

if(fpid ==-1)
        printf("ops\n");
else if(fpid==0)
printf("childdo:9\n");
else
printf("parent do:7\n");
        return 0;
}
