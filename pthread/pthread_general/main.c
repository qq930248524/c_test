#include <stdio.h>
#include <pthread.h>

void *fn_(void *a)
{
    int *test;
    int par2 = 2;
    pthread_t pid1, pid2;
    test = (int *)a;
    printf("this is %d pthread!\n", *test);
    sleep(1);
    pthread_create(&pid2, NULL, fn_, (void *)&par2);
    sleep(3);
    return;
}

void test()
{
    int par1 = 1;
    pthread_t pid1, pid2;
    pthread_create(&pid1, NULL, fn_, (void *)&par1);
    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
    return;
}
int main()
{

    test();
    while(1){};
    return;
}
