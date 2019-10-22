#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int isDig(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}

void splitRead(int fd, char* outFile, int isChild)
{
	char c;
	int temp = open(outFile, O_WRONLY | O_CREAT, 0775);

	int i = 0;
	while(lseek(fd, i, SEEK_SET) != -1 && read(fd, &c, 1) > 0)
	{

		i++;
		if (isChild)
		{
			if(isDig(c))
			{
				write(temp, &c, 1);
			}
		}
		else
		{
			if(!isDig(c))
			{
				write(temp, &c, 1);
			}
		}

	}
	close(temp);
}

int main(int argc, char** argv)
{

	if (argc != 2)
	{
		printf("need an arg\n");
	}

	pid_t pid;
	pid = fork();

	int inputFD = open(argv[1], 0);

	if(pid == 0)
	{
		char fileName[10] = "child.txt";
		splitRead(inputFD, fileName, 0);
	}
	else
	{
		char fileName[10] = "parent.txt";
		splitRead(inputFD, fileName, 1);
	}

	close(inputFD);
	exit(0);
}
