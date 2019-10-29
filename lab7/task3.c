#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[])
{
	pid_t pid;
	int i, infile, outfile;
	char buf;

	if(outfile < 0)
	{
		puts("Ouput file error");
		exit(1);
	}

	pid = fork();

	if(pid < 0)
	{
		puts("Fork failed.");
		exit(1);
	}
	else if(pid == 0)
	{
		outfile = open("foo", O_WRONLY|O_CREAT|O_EXCL, 0755);
		char hello[] = "Hi, Mom.";

		for(i = 0; i < strlen(hello); i++)
		{
			write(outfile, &hello[i], 1);
		}
	}
	else
	{
		wait(&pid);

		infile = open("foo", O_RDONLY);
		printf("My son said, ");

		while(read(infile, &buf, 1) > 0)
		{
			printf("%c", buf);
		}
	}

	close(infile);
	close(outfile);
	return 0;
}
