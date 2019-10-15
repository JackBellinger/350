#include <unistd.h>//getcwd
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>//printf
#include <sys/stat.h>
#include <limits.h>//PATH_MAX
int main()
{

	umask(0);
	mkdir("Dir1", 0777);
	mkdir("Dir2", 0777);
	mkdir("Dir2/Dir21", 0777);
	printf("Copying hello to Dir2/Dir21/hello\n");
	copy("hello", "Dir2/Dir21/hello");
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Current working dir: %s\n", cwd);
	} else {
		perror("getcwd() error");
		return 1;
	}
	printf("Linking hello Dir2/Dir21/hello to Dir1/toHello\n");
	symlink("~/code/350-lab4/task3/Dir2/Dir21/hello", "Dir1/toHello");
	symlink("~/code/350-lab4/task3/Dir2/Dir21", "Dir1/toDir21");

	return 0;
}


int copy(char* inFileName, char* outFileName)
{

	int inFile = open(inFileName, O_RDONLY);
	if(inFile == -1)
	{
		printf("open input file error");
		return -1;
	}

	int outFile = open(outFileName, O_RDWR | O_CREAT, 0666);

	char c;
	while( read(inFile, &c, 1) == 1)
	{
		write(outFile, &c, 1);
	}

	close(inFile);
	close(outFile);
	return 0;
}
