#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#define fifo_name "/tmp/task4_fifo"
#define MAX_BUF_SIZE 255

const int READ_END = 0;
const int WRITE_END = 1;

int main(int argc, char* argv[])
{
    int fd, ret_val, count, nchar;
	const char some_data[] = "123";
	int d_len = strlen(some_data);
	char* buf = calloc(d_len, sizeof(char));

	/* Create the FIFO(named – pipe) */
	ret_val = mkfifo(fifo_name, 0666);
	if((ret_val == -1) && (errno != EEXIST)) {
		perror("Error creating the named pipe");
		exit (1);
	}
	else
	{
		fd = open(fifo_name, O_RDWR);
		nchar = write(fd, some_data, d_len);

        printf("Wrote %d bytes. \n", nchar);
		nchar = read(fd, buf, d_len);
		buf[nchar] = '\0';
		printf("Read %d bytes: %s \n", nchar, buf);
	}
	/* Open the FIFO for reading */
	/* Read from the FIFO */
    free(buf);
    exit(EXIT_FAILURE);
}
