//
// Created by Сергей Абросов on 30.05.2022.
//

#include <signal.h>
#include <stdio.h>

void my_handler(int nsig) {
    if (nsig == 2)
        printf("Receive signal %d, CTRL-C pressed\n", nsig);
    else if (nsig == 3)
        printf("Receive signal %d, CTRL-4 pressed\n", nsig);
}

int main(void) {
    (void)signal(SIGINT, my_handler);
    (void)signal(SIGQUIT, my_handler);

    while(1);
}