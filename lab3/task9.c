#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int palind(int fd1, int fd2)
{
	char word[100];
	char c = '';
	int i = 0;
	while(readlen = read(fd, c, 1))
	{
		if( c == " ")
		{
			
		}
	}
		// write(fd2, buffer, readlen);
	int file1_len = lseek(fd1, 0, SEEK_END);

	int buffer_size = 32;
	char buffer[buffer_size];
	int i, read_len;
	for( i = file1_len-1; i >= 0; i--)
	{
		read_len = pread(fd1, buffer, buffer_size, i);
		pwrite(fd2, buffer, read_len, i);
		// lseek(fd, i, SEEK_SET);
		// read_len = read(fd, buffer, buffer_size);
		// write(fd2, buffer, read_len);
	}
}
int main(int argc, char** argv)
{
	if(argc < 2)
	{
		printf("You need the two file names as arguments");
		return 1;
	}
	umask(0);
	int buffer_size = 1;
	char buffer[buffer_size];
	int fd1 = open(argv[1], O_RDONLY);
	int fd2 = dup(fd1);
	palind(fd1, fd2);

}
