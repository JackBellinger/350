#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 256
voiderr_sys(char *);
int main()
{
	int n, fd[2], size, int1, int2;
	pid_t pid;
	char sline[MAXLINE], rline[MAXLINE];
	if (pipe(fd) < 0) /* creata pipe */
		err_sys("pipe error");
	if ( (pid= fork()) < 0) /*creata child */
		err_sys("fork error");
	else if (pid> 0) /* parent use the pipe to send message to child*/
	{
		close(fd[0]); /* fd[0] need to be close since fd[1] is used for sending data */
		printf("submit two integers\n");
		while( (size = read(STDIN_FILENO, sline, MAXLINE)) > 0)
		{
			write(fd[1], sline, size); /*write to a pipe */
			printf("submit two integers\n");
		}
	}else /* child use pipe to receive message from the parent */
	{
		close(fd[1]); /* fd[1] need to be close since fd[0] is used for receiving data */
		while((n = read(fd[0], rline, MAXLINE))>0) /*read from the pipe */
		{/* chose first two string as two integer */
			if(sscanf(rline, "%d%d", &int1, &int2) == 2)
			{
				sprintf(rline, "%d\n", int1 + int2);
				n = strlen(rline);
				if (write(STDOUT_FILENO, rline, n) != n)
					err_sys("write error");
			}
			else/* if first two string is not integer */
			{
				if (write(STDOUT_FILENO, "invalid args\n", 13) != 13)
					err_sys("write error");
			}
		}//end of while
	} //end of else
	return 0;
}

void err_sys(char *str)
{
	printf("%s \n",str);
	exit (1);
}
