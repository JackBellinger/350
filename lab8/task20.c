#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include <string.h> //memcpy

pthread_mutex_t scores_mutex= PTHREAD_MUTEX_INITIALIZER;

void* get_scores(void* arg)
{
	int* scores = (int*)arg;
	int i,j;
	int tmp = 0;
	for(i = 0; i < 20; i++)
	{//scores[i] = i;
		if(i > 0)
			if(scores[i-1] >= 0)
				scanf("%d", scores+i);
			else
				break;
	}

	for(i=0; i<20; i++)
		for(j=i+1; j<20; j++)
			if(scores[j] < scores[i])
				swap(scores+i, scores+j);
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

	// the following two loops sort the array x in ascending order

			//{
				// mutex so there's no race condition with min max - not neccessary with copy
				// pthread_mutex_lock(&scores_mutex);
				// swap elements
				// swap(scores_copy[i], scores_copy[j]);
				// pthread_mutex_unlock(&scores_mutex);
			//}
	//int median = ((scores_copy[10] + scores_copy[9]) / 2.0);
	//printf("median is %d", median);


	return (void*)sum;
	//pthread_exit(NULL);
}

//prints the min and max of the score list
void* min_max(void* arg)
{
	int* scores = (int*)arg;

	int minmax[2];
	minmax[0] = -1;
	minmax[1] = -1;
	int i;
	for(i = 0; i < 20; i++)
		if(scores[i] >= 0)
			if(scores[i] < minmax[0] || minmax[0] == -1)
				minmax[0] = scores[i];
	minmax[1] = scores[19];
	printf("====%d\n", scores[10]);
	printf("====%d\n", minmax[1]);

	return (void*)minmax;
	//pthread_exit(NULL);
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

	int sum;
	int minmax[2];
	pthread_create(&thread_id[1], NULL, avg, (void*)scores);
	pthread_create(&thread_id[2], NULL, min_max, (void*)scores);
	pthread_join(thread_id[1], (void*)&sum);
	printf("median is %d\n", scores[10]);
	pthread_join(thread_id[2], (void*)minmax);
	printf("min is %d, max is %d\n", minmax[0], minmax[1]);

	pthread_create(&thread_id[3], NULL, clear_buf, (void*)scores);
	pthread_join(thread_id[3], NULL);

	exit(0);
}
