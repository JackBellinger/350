#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int data_processed;
    int file_pipes[2];
    const char some_data[] = "123";
    char buffer[BUFSIZ + 1];
    pid_t pid;

    memset(buffer, '\0' ,sizeof(buffer));

    if(pipe(file_pipes) == 0)
    {
        pid = fork();
    	if(pid == -1)
    	{
        	fprintf(stderr, "Fork Failure");
        	exit(EXIT_FAILURE);
    	}

    	if(pid==0)//child
    	{
    		char wBuffer[BUFSIZ + 1];
			close(file_pipes[1]);//did you mean to say close the write end?
       		(void)execl("pipe4","pipe4", file_pipes[0], (char*)0);
    	    exit(EXIT_FAILURE);
    	}
    	else
    	{
        	data_processed=write(file_pipes[1], some_data, strlen(some_data));
        	close(file_pipes[0]);
        	wait(&pid);
        	printf("%d - wrote %d bytes \n", getpid(), data_processed);
    	}
  	}
    exit(EXIT_SUCCESS);
}
