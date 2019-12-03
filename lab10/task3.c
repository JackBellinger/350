#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/sem.h>

#define MUTEX 0
#define EMPTY 1
#define FULL 2

union semun {
	int val;
	/* for SETVAL */
	struct semid_ds* buf;
	/* for IPC_STAT and IPC_SET */
	unsigned short* array;
	/* for GETALL and SETALL */
};

int semid;
int list[10];
int curr = 0;

void insert_item(int item)
{
	if(curr < 10)
		list[curr++] = item;
	else
		printf("list is full\n");
}
int remove_item()
{
	int i = -1;
	if(curr >= 0)
	{
		i = list[--curr];
		list[curr] = 0;
		return i;
	}
	else
		printf("list is empty\n");
}

void up(int sem_num)
{
	struct sembuf up = {sem_num, 1, 0};
	if(semop(semid, &up, 1) == -1) {perror("semop error");exit(1);}
}

void down(int sem_num)
{
	struct sembuf down = {sem_num, -1, 0};
	if(semop(semid, &down, 1) == -1) {perror("semop error");exit(1);}
}

pthread_t thread_id[2];
void* producer()
{
	int item;
	while(1)
	{
		item = rand() % 9 + 1;
		down(EMPTY);
		down(MUTEX);
		printf("Inserting %d\n", item);
		insert_item(item);
		up(MUTEX);
		up(FULL);
		int i;
		for(i = 0; i < 10; i++)
			printf("%d ", list[i]);
		puts("\n");
		sleep(1); //use this to make it fill up
		//sleep(curr); //use this to make it stay around half full
	}
}

void* consumer()
{
	int item;
	while(1)
	{
		item = rand() % 10;
		down(FULL);
		down(MUTEX);
		item = remove_item();
		up(MUTEX);
		up(EMPTY);
		printf("removed item: %d\n", item);
		int i;
		for(i = 0; i < 10; i++)
			printf("%d ", list[i]);
		puts("\n");
		sleep(2); //use this to make it fill up
		//sleep(10 - curr); //use this to make it stay around half full
	}
}

int main(int argc, char** argv)
{
	key_t key;
	union semun arg;
	if((key = ftok("task3.c", 'J')) == -1)
	{
		perror("ftok Error");
		exit(1);
	}/* create a semaphore set with 1 semaphore: */

	if((semid = semget(key, 3, 0666 | IPC_CREAT)) == -1){perror("semget Error");exit(1);}

	//initialize all of the semaphores
	arg.val = 0;
	if(semctl(semid, FULL, SETVAL, arg) == -1){ perror("semctl Error");exit(1);}
	arg.val = 10;
	if(semctl(semid, EMPTY, SETVAL, arg) == -1){perror("semctl Error");exit(1);}
	arg.val = 1;
	if(semctl(semid, MUTEX, SETVAL, arg) == -1){perror("semctl Error");exit(1);}

	printf("Starting threads\n");
	pthread_create(&thread_id[0], NULL, producer, (void*)&semid);
	pthread_create(&thread_id[1], NULL, consumer, (void*)&semid);

	pthread_join(thread_id[0], NULL);
	pthread_join(thread_id[1], NULL);

	exit(0);
}
