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
    if(mknod(name, S_IFIFO | 0666, 0) < 0)
    {
        printf("Cant1\n");
        return 0;
    }
    fd = open (name, O_RDWR);
    size = write(fd, "privet", 6);
    printf("%ld\n", size);
    char* argv[] = {NULL};
    execv("./bbb", argv);
return 0;
}
