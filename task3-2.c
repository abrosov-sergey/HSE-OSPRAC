#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    pid = fork();

    if (pid == -1) {
        printf("Error");
    } else if (pid == 0) {
        printf("Children");
    } else {
        printf("Parent");
    }
}