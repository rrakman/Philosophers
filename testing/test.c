#include<pthread.h>
#include<unistd.h>
#include<stdio.h>

void *myTurn(void *s)
{
    int i = 0;
    (void)s;
    while(i < 8)
    {
        sleep(1);
        printf("My Turn! %d\n", i);
        i++;
    }
    return NULL;
}

void *yourTurn(void *s)
{
    (void)s;
    int i = 0;
    while(i < 3)
    {
        sleep(2);
        printf("Your Turn! %d\n", i);
        i++;
    }
    return NULL;
}

int main()
{
    pthread_t t1;
    pthread_create(&t1,NULL,myTurn,NULL);
    //pthread_create(&t2,NULL,yourTurn,NULL);
    //pthread_join(t2,NULL);
    yourTurn(NULL);
    // pthread_join(t1,NULL);
    // pthread_detach(t1);
}