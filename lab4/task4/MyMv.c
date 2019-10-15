#include <unistd.h>//getcwd
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>//printf
#include <sys/stat.h>//stat
#include <sys/types.h>
#include <limits.h>//PATH_MAX
#include <string.h>
#include <stdlib.h>
#include <libgen.h>

char *get_filename_ext(const char *filename) {
	const char *dot = strrchr(filename, '.');
	if(!dot || dot == filename) return "";
	return dot + 1;
}
static void get_file_name(char *path) {
	char *bname;
	char *path2 = strdup(path);
	bname = basename(path2);
	printf("%s.%s\n",bname, get_filename_ext(bname));
	free(path2);
}
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
	//second argument is the dir or new filename to move it to
	get_file_name(argv[2]);
	int size = strlen(argv[2]);
	int src_last_backslash_index=strrchr(argv[1],'/') - argv[1];
	if (src_last_backslash_index < 0)
		src_last_backslash_index = 0;
	if( is_reg(argv[1]) )
	{
		if( is_dir(argv[2]))
		{//if the second param is a directory, move the file to there
			printf("Test\n");
			char* index = strrchr(argv[1],'/');
			if(src_last_backslash_index > 0)
				sprintf(argv[2]+size, "/%s", index);
			else
				sprintf(argv[2]+size, "/%s", argv[1]);
			//sprintf(new_filepath, "%s/%s", argv[2], argv[1]+src_last_backslash_index);
			// /strcat(new_filepath, argv[1]+ src_last_backslash_index);
			link(argv[1], argv[2]);//Returns: 0 if OK, 1 on error
		}
		else
		{
			link(argv[1], argv[2]);
			unlink(argv[1]);
		}

	}
	else
		printf("Arg 1 needs to be a regular file.");

	umask(0);
}
