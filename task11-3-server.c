#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

int main(void)
{
    int msqid;
    int i;
    int len;

    char pathname[]="task11-3-client.c";
    key_t  key;

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

    while (true) {
        len = sizeof(struct mymsgbuf) - 8;

        if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, len, -1000000000, 0)) < 0) {
            printf("Can\'t receive message\n");
            exit(-1);
        }

        printf("Message = %ld, info = %f\n", mybuf.mtype, mybuf.flt);

        mybuf.flt = mybuf.flt * mybuf.flt;

        len = sizeof(struct mymsgbuf) - 8;

        printf("Answer = %d, and float = %f\n", mybuf.mtype, mybuf.flt);

        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
            printf("Server can\'t answer the request\n. Errno: %d", errno);
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }

        printf("Sended\n");
    }
}
