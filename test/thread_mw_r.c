#include<pthread.h>
#include <unistd.h>

typedef struct 
{
    int i;
    pthread_mutex_t m;
}m_int;


void *reading(void *p)
{
    m_int *i = p;
    int j = 0;

    while (1)
    {
        if (i->i < 42)
            j +=  i->i;
        else
            j--;
    }
    return (0);
}

void *writeing(void *p)
{
    m_int *i = p;
    int j = 0;

    while (1)
    {
        pthread_mutex_lock(&(i->m));
        i->i++;
        pthread_mutex_unlock(&(i->m));
    }
    return (0);
}

int main ()
{
    m_int ver;
    pthread_t p;
    pthread_attr_t ta;

    ver.i = 0;
    pthread_mutex_init(&(ver.m), NULL);
    pthread_create(&p,NULL, reading, &ver);
    pthread_create(&p,NULL, writeing, &ver);
    pause();
    return 0;
}