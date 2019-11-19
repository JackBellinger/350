#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int data_processed, nchar;
    int file_pipes[2];
    int parent_msg_pipe[2];

    const char some_data[] = "Hi There, Kiddo";
    char buffer[BUFSIZ + 1];
    pid_t pid;

    memset(buffer, '\0' ,sizeof(buffer));

    if(pipe(file_pipes) == 0 && pipe(parent_msg_pipe) == 0)
    {
        pid = fork();
    	if(pid == -1){

        	fprintf(stderr, "Fork Failure");
        	exit(EXIT_FAILURE);
    	}

    	if(pid==0)//child
    	{
    		char wBuffer[BUFSIZ + 1];
			close(file_pipes[1]);//did you mean to say close the write end?
            close(parent_msg_pipe[0]);
       		(void)execl("twoPipesChild","twoPipesChild", file_pipes[0], parent_msg_pipe[1], (char*)0);
    	    exit(EXIT_FAILURE);
    	}
    	else
    	{
            close(file_pipes[0]);
            close(parent_msg_pipe[1]);
        	data_processed=write(file_pipes[1], some_data, strlen(some_data));
            nchar = read(parent_msg_pipe[0], buffer, 6);
        	wait(&pid);
        	printf("Parent:%d - wrote %d bytes \n", getpid(), data_processed);
            printf("Parent:%d - read %d bytes: %s\n", getpid(), nchar, buffer);
    	}
  	}
    exit(EXIT_SUCCESS);
}
