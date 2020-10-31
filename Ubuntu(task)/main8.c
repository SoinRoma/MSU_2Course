#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
int fd, result;
    size_t size;
    char resstring[6];
    char name[] = "aaa.fifo";
    (void)umask(0);

    fd = open(name, O_RDWR);
    read(fd, resstring, 6);
    printf("%s\n", resstring);
close(fd);
}
