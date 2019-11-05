#include<stdio.h>
#include<stdlib.h>
int main(int argc, char** argv)
{
	int cmd_len = 0;
	int i, j;
	for(i = 1; i < argc; i++)
		cmd_len += strlen(argv[i]) + 1;
	char* cmd[cmd_len];
	for(i = 1; i < argc; i++)
	{
		strcat(cmd, argv[i]);
		strcat(cmd, " ");
	}
	printf("command: %s\nresult: \n\n", cmd);

	char buf[BUFSIZ]; /* BUFSIZ =1024 defined in stdio.h */
	FILE *ptr;
	if((ptr = popen(cmd, "r")) != NULL)
		while(fgets(buf, BUFSIZ, ptr) != NULL)
			(void) printf("%s", buf);
	pclose(ptr);

	return 0;
}
