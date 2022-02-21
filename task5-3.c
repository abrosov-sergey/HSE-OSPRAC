#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd[2], result;
    int size = 0;

    if (pipe(fd) < 0) {
        printf("Can\'t open parent -> child pipe\n");
        exit(-1);
    }

    result = fork();

    if (result > 0) {
        if (close(fd[0]) < 0) {
            printf("parent: Can\'t close reading side of parent -> child pipe\n");
            exit(-1);
        }

        char *str = (char*)malloc(2);
        size = write(fd[1], str, 1000000);
        printf("Size of pipe: %d\n", size);

        if (close(fd[1]) < 0) {
            printf("parent: Can\'t close writing side of pipe\n");
            exit(-1);
        }
    } else if (result < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else {
        if (close(fd[1]) < 0) {
            printf("child: Can\'t close writing side of parent -> child pipe\n");
            exit(-1);
        }

        while (1) {
            char temp;
            if (read(fd[0], &temp, 1) < 1)
            {
                break;
            }
        }

        if (close(fd[0]) < 0) {
            printf("child: Can\'t close reading side of pipe\n");
            exit(-1);
        }

        exit(-1);
    }

    return 0;
}