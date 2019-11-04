#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include <string.h> //memcpy

pthread_mutex_t scores_mutex= PTHREAD_MUTEX_INITIALIZER;

void* get_scores(void* arg)
{
	int* scores = (int*)arg;
	int i;
	for(i = 0; i < 20; i++)
		scores[i] = i;
		//scanf("%d", scores+i)
	//return scores;
	pthread_exit(NULL);
}

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *x;
	*y = temp;
}
//calculates the average + median score + prints
void* avg(void* arg)
{
	int* scores = (int*)arg;
	int i, j, sum = 0;
	for( i = 0; i < 20; i++)
		sum += scores[i];
	printf("average is %d\n", sum / 20);

	int scores_copy[20];
	memcpy((void*)scores_copy, scores, 20*sizeof(int));
	// the following two loops sort the array x in ascending order
	for(i=0; i<20; i++)
		for(j=i+1; j<20; j++)
			if(scores_copy[j] < scores_copy[i])
				swap(scores_copy+i, scores_copy+j);
			//{
				//mutex so there's no race condition with min max - not neccessary with copy
				//pthread_mutex_lock(&scores_mutex);
				// swap elements
				//swap(scores_copy[i], scores_copy[j]);
				//pthread_mutex_unlock(&scores_mutex);
			//}
	//int median = ((scores_copy[10] + scores_copy[9]) / 2.0);
	//printf("median is %d", median);
	printf("median is %d\n", scores[10]);

	//return scores;
	pthread_exit(NULL);
}

//prints the min and max of the score list
void* min_max(void* arg)
{
	int* scores = (int*)arg;
	int i, min = -1, max = 0;
	for(i = 1; i < 20; i++)
	{
		if(scores[i] < min | min ==-1)
			min = scores[i];
		if(scores[i] > max)
			max = scores[i];
	}

	//return scores;
	pthread_exit(NULL);
}

void* clear_buf(void* arg)
{
	int* buf = (int*)arg;
	int i;
	printf("cleared buff ");
	for(i = 0; i < 20; i++)
	{
		buf[i] = 0;
		printf("%d", buf[i]);
	}
	printf("\n");
	//return buf;
	pthread_exit(NULL);
}

int main(int argc, char** argv)
{
	int* scores = calloc(20, sizeof(int));

	pthread_t thread_id[4];
	pthread_create(&thread_id[0], NULL, get_scores, (void*)scores);
	pthread_join(thread_id[0], NULL);

	int i;
	printf("filled buff ");
	for(i = 0; i < 20; i++)
		printf("%d", scores[i]);
	printf("\n");
	pthread_create(&thread_id[1], NULL, avg, (void*)scores);
	pthread_create(&thread_id[2], NULL, min_max, (void*)scores);
	pthread_join(thread_id[1], NULL);
	pthread_join(thread_id[2], NULL);

	pthread_create(&thread_id[3], NULL, clear_buf, (void*)scores);
	pthread_join(thread_id[3], NULL);

	exit(0);
}
