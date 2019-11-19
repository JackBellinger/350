#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
	int i;
	sigset_t sigs, old;

	sigemptyset(&sigs);

	sigaddset(&sigs, SIGINT);

	sigaddset(&sigs, SIGQUIT);

	sigprocmask(SIG_BLOCK, &sigs, &old);

	for(i = 1; i <= 5; i++){
		printf("Int and quit blocked %d \n", i);
		sleep(1);
	}
	sigset_t unblock;
	sigemptyset(&unblock);
	sigdelset(&unblock, SIGINT);

	sigprocmask(SIG_UNBLOCK, &unblock, &old);

	for(i = 1; i <= 5; i++){
		printf("Only quit blocked %d \n", i);
		sleep(1);
	}

	return 0;
}
