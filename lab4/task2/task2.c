#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		printf("need input and output file args");
		return -1;
	}
	
	umask(0);
	int copyErr = copy(argv[1], argv[2]);
	return copyErr;

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
