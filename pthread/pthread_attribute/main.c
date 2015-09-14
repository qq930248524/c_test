#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

int ret = 0;
pthread_mutex_t mutex;


void *fun1()
{
    printf("this is thread1!\n");
    while(1){
        sleep(1);
        //pthread_mutex_lock(&mutex);
        printf("ret1 = %d\n", ret);
        ret++;
        //pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}
void *fun2()
{
    printf("this is thread2\n");
    while(1){
        sleep(1);
        //pthread_mutex_lock(&mutex);
        printf("ret2 = %d\n", ret);
        ret++;
        //pthread_mutex_unlock(&mutex);
    }
    return;
}

int main()
{
    pthread_t pt_1 = 0;
    pthread_t pt_2 = 0;
    pthread_attr_t attr = {0};

    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_mutex_init(&mutex, NULL);
    if(pthread_create(&pt_1, &attr, fun1, NULL) != 0)
    {
        perror("pthread pt1 create!\n");
    }
    if(pthread_create(&pt_2, NULL, fun2, NULL) != 0)
    {
        perror("pthread pt2 create!\n");
    }
    while(1)
    {
    }

    pthread_join(pt_2, NULL);

    return 0;
}
