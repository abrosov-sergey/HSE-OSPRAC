#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    int n;
    char inf[24];

    (void) umask(0);
    if ((n = open("myfile", O_RDWR | O_CREAT, 0666)) < 0) {
        printf("Can not opening file\n");
        exit(-1);
    }

    read(n, inf, 14);
    printf("%s\n", inf);

    return 0;
}
