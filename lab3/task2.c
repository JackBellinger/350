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
	char buffer[1];
	int fd = open(argv[1], O_RDONLY);
	int fd2 = open(argv[2], O_RDWR | O_CREAT, 0666);
	while(read(fd, buffer, 1))
		write(fd2, buffer, 1);
	close(fd);
	close(fd2);

	return 0;
}
