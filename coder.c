#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include "codec.h"
#include <stdint.h>
#include <string.h>

#define IDX_N 1024 /* in this example */

/* this structure will wrap all thread's data */
typedef struct work
{
	size_t start, end;
	pthread_t tid;
} work, *pwork;

char *sign;
char buffer[IDX_N]; // 1024 as mentioned

void *method(void *arg)
{
	pwork w = (pwork)arg;
	/* now each thread can learn where it should start and stop
	 * by examining indices that were passed to it in argument */
	for (size_t i = w->start; i < w->end; i++)
		printf("%d\n", (buffer[i]));
	return NULL;
}

int main(int argc, char const *argv[])
{

	/**
	 * Less than 3 arguments
	 */
	if (argc != 3)
	{
		printf("Too few arguments ");
		printf("USAGE: ./coder <key> < -e or -d for encrypt/decrypt>");
		exit(0);
	}

	// Get args from input (key & flag)
	int given_key = atoi(argv[1]); // given key
	sign = argv[2];				   // -d or -e

	// Input file/object/whatever
	if (fgets(buffer, IDX_N, stdin) == NULL)
	{
		puts("erorr eccur");
	}
	int n = sysconf(_SC_NPROCESSORS_ONLN); // Number of processors

	work w[n];
	size_t idx_start, idx_end, idx_n = IDX_N / n;
	idx_start = 0;
	idx_end = idx_start + idx_n;
	for (size_t i = 0; i < n; ++i)
	{
		w[i].start = idx_start; /* starting index */
		w[i].end = idx_end;		/* ending index */
		/* pass the information about starting and ending point for each
		 * thread by pointing it's argument to appropriate work struct */
		pthread_create(&w[i].tid, NULL, method, (void *)&w[i]);
		idx_start = idx_end;
		idx_end = (idx_end + idx_n < IDX_N ? idx_end + idx_n : IDX_N);
	}

	for (size_t i = 0; i < n; ++i)
	{
		pthread_join(w[i].tid, NULL);
	}

	return 0;
}
