#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
 int main(void)
 {
     int a,b;
uid_t getuid(void);
gid_t getgid(void);
a = getuid();
b = getgid();

printf ("%d\n%d", a,b);
     return 0;
}
