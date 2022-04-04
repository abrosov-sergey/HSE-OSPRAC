#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

void *mythread(void *dummy)
{
    pthread_t mythid;

    mythid = pthread_self();

    a = a + 1;
    printf("Thread %u, Calculation result = %d\n", mythid, a);
    return NULL;
}

int main()
{
    pthread_t thid, mythid, secondThid;
    int result1, result2;

    // First additional thread.
    result1 = pthread_create (&thid, (pthread_attr_t *)NULL, mythread, NULL);
    if (result1 != 0) {
        printf ("Error on thread create, return value = %d\n", result1);
        exit(-1);
    }
    printf("Thread created, thid = %u\n", thid);

    // Create? second thread.
    result2 = pthread_create (&secondThid, (pthread_attr_t *)NULL, mythread, NULL);
    if (result2 != 0) {
        printf ("Error on thread2 create, return value = %d\n", result2);
        exit(-1);
    }
    printf("Thread2 created, thid2 = %u\n", secondThid);

    mythid = pthread_self();
    a = a + 1;

    printf("Thread %u, Calculation result = %d\n", mythid, a);
    pthread_join(thid, (void **)NULL);
    pthread_join(secondThid, (void **)NULL);

    return 0;
}