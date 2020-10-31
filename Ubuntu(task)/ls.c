#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<dirent.h>
#include<fcntl.h>
#include<time.h>
int main()
{
int fd, i;
DIR *dir;
char *name ="./";
struct stat buf;
struct dirent *rd;
char *date;
dir=opendir(name);
while((rd=readdir(dir))!=NULL)
{
stat(rd->d_name,&buf);
printf("%s\t", rd->d_name);
printf("%ld\t",buf.st_size);
printf("%d\t",buf.st_mode);
printf("%d\t",buf.st_gid);
printf("%d\t",buf.st_uid);
printf("%s\n",ctime(&buf.st_ctime));
}
return 0;
}
