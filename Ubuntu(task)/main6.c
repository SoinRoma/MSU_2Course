#include<fcntl.h>
#include<stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(void)
{
const char *path="./main6.c";
int a=open(*path,"0_RDONLY");
int b=open(*path,"0_RDWR,0777");
printf("%d\n %d\n",a,b);
return 0;
}
