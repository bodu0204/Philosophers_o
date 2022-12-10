#include<pthread.h>
#include <unistd.h>

void *writeing(void *p)
{
    int *i = p;
    int j = 0;

    while (1)
    {
        (*i)++;
    }
    return (0);
}

int main ()
{
    int ver = 0;
    pthread_t p;
    pthread_attr_t ta;

    pthread_create(&p,NULL, writeing, &ver);
    pthread_create(&p,NULL, writeing, &ver);
    pause();
    return 0;
}