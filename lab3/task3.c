#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char** argv)
{
	if(argc < 2)
	{
		printf("You need the two file names as arguments")
		return 1;
	}
	umask(0);
	char buffer[32];
	int fd = open(argv[1], O_RDONLY);
	int fd2 = open(argv[2], O_RDWR | O_CREAT, 0770);
	int readlen = 0;
	while(readlen = read(fd, buffer, 32))
		write(fd2, buffer, readlen);
	close(fd);
	close(fd2);

	return 0;
}
