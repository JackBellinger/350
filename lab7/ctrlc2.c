#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig)
{
	printf("\t OUCH! - I got signal %d. \n", sig);

	// Converts Ctrl+C back to it's default operations
	signal(SIGINT, SIG_DFL);
}

int main(int argc, char* argv[])
{
	struct sigaction act;

	act.sa_handler = ouch;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	// Sets Ctrl+C to trigger the ouch() function
	sigaction(SIGINT, &act, NULL);

	// Sets Ctrl+\ to trigger the ouch() function
	//sigaction(SIGQUIT, &act, NULL);

	while(1)
	{
		printf("Hello, World! \n");
		sleep(1);
	}

	return 0;
}
