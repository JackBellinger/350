#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

//calculates the factorial of num iteratively
void* sumup(void* arg)
{
	int num = *(int*)arg; //convert the void ptr to an int and get the value
	int i, sum = 0;
	for( i = 0; i <= num; i++)
		sum += i;

	return (void*)sum;
}
void* factorial(void* arg)
{
	int num = *(int*)arg; //convert the void ptr to an int and get the value
	int i, prod = 1;
	for(i = 1; i <= num; i++)
		prod *= i;

	return (void*)prod;
}
int main(int argc, char** argv)
{
	int n1 = atoi(argv[1]);
	int n2 = atoi(argv[2]);
	void* sum;
	void* prod;

	pthread_t thread_id[2];

	pthread_create(&thread_id[0], NULL, sumup, (void*)&n1);
	pthread_create(&thread_id[1], NULL, factorial, (void*)&n2);

	pthread_join(thread_id[0], &sum);
	pthread_join(thread_id[1], &prod);

	printf("sum up %d\n", (int)sum);
	printf("factorial %d\n", (int)prod);


	exit(0);
}
