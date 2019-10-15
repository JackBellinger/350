#include <unistd.h>//getcwd
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>//printf
#include <sys/stat.h>//stat
#include <sys/types.h>
#include <limits.h>//PATH_MAX
#include <string.h>
#include <stdlib.h>

//first argument is the file path of the file that should be moved
//second argument is the path to either an unused filename in a dir that exists or
//	just a directory

int is_reg(const char *path)
{
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISREG(path_stat.st_mode);
}
int is_dir(const char *path){
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISDIR(path_stat.st_mode);
}

int main(int argc, char** argv)
{
	// if (argc != 3)
	// 	printf("Need 2 args");
	// else
	// {
	// 	printf("isreg arg1 %d\n", is_reg(argv[1]));
	// 	printf("isreg arg2 %d\n", is_reg(argv[2]));
	// }

	//path of where to move, if dir must exist,
	//if file dir must exist + file must not

	//first argument is the file to move
	printf("Hello");
	//second argument is the dir or new filename to move it to
	char* move_this_file_path = argv[1];
	char* move_to = malloc(strlen(argv[2]) + 10);
	int size = strlen(argv[2]);
	strcat(move_to, argv[2]);
	printf("hello");
	int dest_last_backslash_index=strrchr(argv[2],'/') - argv[2];
	if( dest_last_backslash_index != strlen(argv[2])-1 )
		strcat(argv[2], '/');
	int src_last_backslash_index=strrchr(argv[1],'/') - argv[1];

	printf("dest: %s | %d", move_to, dest_last_backslash_index);
	printf("src: %s | %d", move_this_file_path, src_last_backslash_index);
	char* src = argv[1] + src_last_backslash_index;
	printf("test %s", src);
	char* file_name;
	strncpy (file_name, argv[1] + src_last_backslash_index,  10);

	if( is_reg(argv[1]) )
	{
		if( is_dir(argv[2]))
		{//if the second param is a directory, move the file to there
			if( dest_last_backslash_index != strlen(argv[2])-1 )
				strcat(argv[2], '/');
			printf("Test\n");
			char new_filepath[strlen(argv[2]) + 10];
			strcat (new_filepath, argv[2]);
			strcat(new_filepath, file_name);
			link(argv[1], argv[2]);//Returns: 0 if OK, 1 on error
		}

	}
	else
		printf("Arg 1 needs to be a regular file.");

	umask(0);
}
