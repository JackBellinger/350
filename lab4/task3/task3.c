#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/stat.h>

int main()
{

	umask(0);
	mkdir("Dir1", 0777);
	mkdir("Dir2", 0777);
	mkdir("Dir2/Dir21", 0777);

	copy("hello", "Dir2/Dir21/hello");

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
