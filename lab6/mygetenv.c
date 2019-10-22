#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char* mygetenv(char* search)
{
	char *var = *environ;
	int i;
	for( i = 1; var != 0; i++ )
	{
		char* eq = strchr(var, '=');
		int index = eq - var;
		char* varname = malloc(index * sizeof(char));
		strncpy(varname, var, index);
		if( strcmp(varname, search) == 0)
		{
			free(varname);
			return eq+1;
		}
		free(varname);
		var = *(environ+i);
	}
	return NULL;
}

int main(int argc, char** argv) {
	char* search;
	if( argc == 2)
		search = argv[1];
	else
	{
		printf("Since no arg provided, searching for LOGNAME\n");
		search = "LOGNAME";
	}
	char* result = mygetenv(search);
	if(result != NULL)
		printf("%s=%s\n", search, result);
	else
		printf("%s not found\n", search);
	return 0;
}
