#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>

int count = 0;
pthread_t thread_id[2];

void* producer()
{
	while(1)
	{
		if(count == 10)
		{
			puts("producer pause");
			pause();
		}
		count ++;
		if(count == 1)
			pthread_kill(thread_id[1], SIGCONT);
		printf("producer count: %d\n", count);

	}
}

void* consumer()
{
	while(1)
	{
		if(count == 0)
		{
			puts("consumer pause");
			pause();
		}
		count --;
		if(count == 10)
			pthread_kill(thread_id[0], SIGCONT);
		printf("consumer count: %d\n", count);
	}
}

int main(int argc, char** argv)
{


	pthread_create(&thread_id[0], NULL, producer, NULL);
	pthread_create(&thread_id[1], NULL, consumer, NULL);

	pthread_join(thread_id[0], NULL);
	pthread_join(thread_id[1], NULL);

	exit(0);
}
