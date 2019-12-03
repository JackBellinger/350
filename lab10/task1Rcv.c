/*spock.c read message from the message queue *//* created by kirt.c                          */
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <string.h>

typedef struct my_msgbuf {
	long mtype;
	char mtext[200];
}msgbuf;

int main(void){
	msgbuf buf;
	strcpy(buf.mtext, "hello");
	int msqid;
	key_t key;
	/* create a key same as kirt.c */
	if((key = ftok("task1Rcv.c", 'B')) == -1) {
		perror("ftok error");
		exit(1);
	}
	/* open message queue already created by kirk.c */
	if((msqid = msgget(key, 0644)) == -1) {
		perror("msgget error");
		exit(1);
	}
	printf("spock: ready to receive messages, captain.\n");
	for(;;)
	{
		 /* get each message from the message queue */
		if(msgrcv(msqid, (msgbuf *)&buf, sizeof(buf.mtext), 0, 0) == -1) {
			perror("msgrcv error");
			exit(1);
		}
		int one = 0;
		int two = 0;
		printf("%s", buf.mtext);
		sscanf(buf.mtext, "%d%d", &one, &two);
		printf("Sum: %d\n", one + two);
	}

	return 0;

}
