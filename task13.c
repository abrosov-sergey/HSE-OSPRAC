#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;
    int count = 0;

    char path[256] = "a.txt";
    char prev_name[256] = "a.txt";
    char name[256] = "a0";
    char s[256];

    if ((fd = open(path, O_CREAT | O_EXCL, 0666)) < 0) {
        printf("Произошла ошибка при создании файла\n");
        exit(-1);
    }

    do {
        strcpy(s, name);

        if (symlink(prev_name, s) < 0) {
            printf("Произошла ошибка при создании ссылки\n");
            exit(-1);
        }

        ++count;
        size_t destination_size = sizeof(name);

        strncpy(prev_name, name, destination_size);
        prev_name[destination_size - 1] = '\0';

        strcpy(name, "a");

        char buffer[4];

        sprintf(buffer, "%d", count);
        strcat(name, buffer);

        name[sizeof(name) - 1] = '\0';

        if (close(fd) < 0) {
            exit(-1);
        }
    } while ((fd = open(s, O_RDONLY, 0666)) >= 0);

    printf("Итоговое количество: %d\n", --count);

    return 0;
}
