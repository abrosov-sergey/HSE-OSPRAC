//
// Created by Сергей Абросов on 16.05.2022.
//

#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int msqid;
    int i;
    int len;

    char pathname[]="task11-3-client.c";
    key_t  key;

    pid_t pid = getpid();

    float num;

    struct mymsgbuf
    {
        long mtype;
        pid_t pid;
        float flt;
    } mybuf;

    if ((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t get msqid\n");
        exit(-1);
    }

    len = sizeof(struct mymsgbuf) - 8;
    scanf("%f", &num);
    mybuf.flt = num;
    mybuf.mtype = pid;

    printf("Send data\n");

    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
        printf("Server can\'t receive the request\n");
        exit(-1);
    }

    if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, len, pid, 0)) < 0) {
        printf("Can\'t receive response from server\n");
        exit(-1);
    }

    printf("Feedback: type = %ld, info = %f\n", mybuf.mtype, mybuf.flt);

    return 0;
}
