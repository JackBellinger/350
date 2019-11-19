#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int READ_END = 0;
const int WRITE_END = 1;

int main(int argc, char* argv[])
{
    int file_pipes[2];
    int nchar;
    const char some_data[] = "123";
	int d_len = strlen(some_data);
    char* buf = calloc(d_len, sizeof(char));

    if(pipe(file_pipes) == 0)
    {
        nchar = write(file_pipes[WRITE_END], some_data, d_len);

        printf("Wrote %d bytes. \n", nchar);

        nchar = read(file_pipes[READ_END], buf, d_len);

        printf("Read %d bytes: %s \n", nchar, buf);

        //free(buf);
        exit(EXIT_SUCCESS);
    }
    free(buf);
    exit(EXIT_FAILURE);
}
