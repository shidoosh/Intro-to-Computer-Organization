#include <stdio.h>
#include <pthread.h>
#include <string.h>


typedef struct threadArg
{
    int tag;
    int num;
}threadArg;

void *thread (void *vargp);
int Leo (int n);
int Fib (int m);

int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        printf("Invalid input. Pass a valid N \n");
        return 1;
    }
    
    char* val = argv[1];
    int i;
    int t=0;
    for(i = 0; i<strlen(val); i++)
        t = t*10 + (val[i] - '0');

    if(t <= 1)
        printf("[%d]\n", 0);

    else
    {
        printf("(%d \n", 0);
        threadArg l;
        pthread_t lThread;
        l.tag = 1;
        l.num = t-1;
        pthread_create(&lThread, NULL, thread, (void*)&l);
        pthread_join(lThread, NULL);
        
        threadArg r;
        r.tag = 1 + Leo(t-1);
        pthread_t rightThread;
        r.num = t-2;
        pthread_create(&rightThread, NULL, thread, (void*)&r);
        pthread_join(rightThread, NULL);
        printf("%d) \n", 0);
    }
    return 0;
}


void *thread (void *vargp)
{
    
    if (vargp == NULL)
        return NULL;
    
    threadArg curr = *(threadArg*)(vargp);
    
    if(curr.num <= 1)
    {
        printf("[%d]\n", curr.tag);
        return NULL;
    }
    
    
    printf("(%d \n", curr.tag);
    

    threadArg left;

    pthread_t leftThread;
    left.tag = curr.tag + 1;
    left.num = curr.num - 1;
    pthread_create(&leftThread, NULL, thread, (void*)&left);
    pthread_join(leftThread, NULL);
    

    threadArg right;

    right.tag = (curr.tag + 1 + Leo(curr.num - 1));

    pthread_t rightThread;
    right.num = curr.num - 2;
    pthread_create(&rightThread, NULL, thread, (void*)&right);
    pthread_join(rightThread, NULL);
    
    printf("%d)\n", curr.tag);
    return NULL;
}

int Leo(int n)
{
    return (2* Fib(n+1)-1);
}

int Fib (int n)
{
    if (n == 0)
        return 0;
    else if(n == 1 || (n == 2))
        return 1;
    int count = 0;
    count = Fib(n-1) + Fib(n-2);
    return count;
}
