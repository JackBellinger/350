#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

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
	int fd = open(argv[1], O_RDONLY);
	int fd2 = open(argv[2], O_RDWR | O_CREAT, 0760);
	dup2(fd2, 1);
	int readlen = 0;
	while(readlen = read(fd, buffer, buffer_size))
	{
		int x = (int)buffer[0];
		printf("%d", x);
	}
	close(fd);
	close(fd2);

	return 0;
}
