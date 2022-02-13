#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
    pid_t pid;
    
    pid = fork();

    if (pid == -1) {
        printf("Error");
    } else if (pid == 0) {
        printf("Children");
        execle("/bin/ls", "-l", NULL, envp);
    } else {
        wait(0);
        printf("Parent");
    }
}
