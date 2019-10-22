#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv)
{
	if(argc != 5)
	{
		printf("need 4 args");
		exit(1);
	}
	//need to dereference argv b/c char pointers can't be cast to int
	int Nc = *argv[1] - '0';
	int Np = *argv[2] - '0';
	int Tc = *argv[3] - '0';
	int Tp = *argv[4] - '0';

	pid_t pid;
	char* message;

	printf( "fork program starting\n" );
	pid = fork();
	switch(pid)
	{
		case -1:
			perror("fork failed!");
			exit(1);
		case 0:
			message = "this is the child";
			break;
		default:
			message = "this is the parent";
			break;
	}
	//need 2 counters since there's 2 processes, don't want race condition

	if(pid == 0)//child
	{
		for(; Nc > 0; Nc--)
		{
			puts(message);
			sleep(Tc);
		}
	}
	else if(pid != 0)//parent
	{
		int stat_val;
		pid_t child_pid;
		child_pid = wait(&stat_val);

		for(; Np > 0; Np--)
		{
			puts(message);
			sleep(Tp);
		}
	}

	exit(0);
}
