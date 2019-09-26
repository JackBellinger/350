#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char** argv)
{
	if(argc < 2)
	{
		printf("You need the three file names as arguments");
		return 1;
	}
	umask(0);
	int buffer_size = 1;
	char buffer[buffer_size];
	int fd = open(argv[1], O_RDONLY);
	int fd2 = open(argv[2], O_RDONLY);
	int fd12 = open(argv[3], O_RDWR | O_CREAT, 0760);

	int file1_len = lseek(fd, 0, SEEK_END);
	int file2_len = lseek(fd2, 0, SEEK_END);

	int i, read_len;
	for( i = 0; i < file1_len; i++)
	{
		lseek(fd, i, SEEK_SET);
		read_len = read(fd, buffer, buffer_size);
		write(fd12, buffer, read_len);
	}
	for( i = 0; i < file2_len; i++)
	{
		lseek(fd2, i, SEEK_SET);
		read_len = read(fd2, buffer, buffer_size);
		write(fd12, buffer, read_len);
	}
	// same as this why use lseek?
	// int readlen = 0;
	// while(readlen = read(fd, buffer, 32))
	// 	write(fd12, buffer, readlen);
	// while(readlen = read(fd2, buffer, 32))
	// 	write(fd12, buffer, readlen);
	close(fd);
	close(fd2);

	return 0;
}
