#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
    FILE *f = fopen("task7-1.c", "r");
    char *buffer;
    int current = 0;
    int shmid;
    char pathname[] = "task7-1w.c";
    key_t key;

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Cannot generate key\n");
        exit(-1);
    }

    if ((shmid = shmget(key, 1000 * sizeof(char), 0666 | IPC_CREAT)) < 0) {
        printf("Cannot create shared memory\n");
        exit(-1);
    }

    if ((buffer = (char *) shmat(shmid, NULL, 0)) == (char *) (-1)) {
        printf("Cannot attach shared memory\n");
        exit(-1);
    }

    while (!feof(f) & current < 10000) {
        buffer[current] = fgetc(f);
        current++;
    }

    if (shmdt(buffer) < 0) {
        printf("Cannott detach shared memory\n");
        exit(-1);
    }

    fclose(f);

    return 0;
}