#include "codec.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include <sys/sysinfo.h>

#include <unistd.h>





#define BUFFERSIZE 1024

//
// boss/worker pthreads model
// the boss will create threads to handle incoming requests
//
//

void task1()
{
    printf("task 1\n");
}

void task2()
{
    printf("task 2\n");
}

void task3()
{
    printf("task 3\n");
}

int main(int argc, const char *argv[])
{
    pthread_t thread1 = NULL, thread2 = NULL, thread3 = NULL;
    // the manager/boss main thread
    // the manager will create a pool of threads ahead of time to serve
    // the requests .. in this example they are created when a request comes

    int n = sysconf(_SC_NPROCESSORS_ONLN); // get number of processors

    while (n)
    {
        // get a data from CMD
        char buffer[BUFFERSIZE];
        fgets(buffer, BUFFERSIZE, stdin);
        printf("Read: %s", buffer);


        switch (n)
        {
        case 1:
            pthread_create(&thread1, NULL, (void *)task1, NULL);
            break;
        case 2:
            pthread_create(&thread2, NULL, (void *)task2, NULL);
            break;
        default:
            pthread_create(&thread3, NULL, (void *)task3, NULL);
            break;
        }
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    printf("done!\n");
    return 0;
}

/*

n = sysconf(_SC_NPROCESSORS_ONLN); // get number of processors
    pthread_t threads[n];



   for (int count = 0; count < n; ++count)
    {
        if (pthread_create(&(threads[count]), NULL, (void*)thread, NULL) != 0)
        {
            fprintf(stderr, "error: Cannot create thread # %d\n", count+1);
            break;
        }                                
    }
    for (int i = 0 ; i< n; i++){
        pthread_join(threads[i], NULL);            
    }

*/