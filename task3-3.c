#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
    char **now;

    printf("Process:\n");
    printf("\tParameters:\n");

    for (now = argv; *now; now++) {
        printf("\t\t%s\n", (*now));
    }

    printf("\t\tEnvironment:\n");

    for (now = envp; *now; now++) {
        printf("\t\t%s\n", *now);
    }
}