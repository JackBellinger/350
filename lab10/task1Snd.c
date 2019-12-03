/* kirt.c get lines of text and added into the message queue *//* Then, the message queue is then read by spock.c		   */
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
/* user message type with 200 byte per message */
typedef struct my_msgbuf {
	long mtype;
	char mtext[200];
}msgbuf;
int main(void){
	msgbuf buf;
	int msqid;
	key_t key;
	/*create a key for create message queue */
	if((key = ftok("task1Rcv.c", 'B')) == -1)
	{
		perror("ftok error");
		exit(1);
	}
	/*create a message queue */
	if((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
	perror("msgget error");
		exit(1);
	}

	//char* input = (char*) calloc(256, sizeof(int));
	printf("Enter lines of text, ^D to quit:\n");
	buf.mtype = 1;

	// Reading in data from the user
	while(fgets(buf.mtext, 256, stdin), !feof(stdin))
	{
		// Sending the struct with the two ints to the message queue
		if (msgsnd(msqid, (msgbuf *) &buf,  sizeof(buf.mtext), 0) == -1)
		{
			perror("msgsnd() error");
		}
		puts("Enter two inerger values...");
	}

	/* Now remove message queue by calling msgclt */
	if(msgctl(msqid, IPC_RMID, NULL) == -1) {
		perror("msgctl error");
		exit(1);
	}

	exit(0);

}
