#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utmp.h>

char* myasctime(const struct tm *timeptr)
{
	char* wDay;
	switch(timeptr->tm_wday)
	{
		case 0:
			month = malloc(6 * sizeof(char));
			mon = "January";
			break;
		case 1:
			month = malloc(6 * sizeof(char));
			mon = "February";
			break;
		case 2:
			month = malloc(7 * sizeof(char));
			mon = "March";
			break;
		case 3:
			month = malloc(9 * sizeof(char));
			mon = "April";
			break;
		case 4:
			month = malloc(8 * sizeof(char));
			mon = "May";
			break;
		case 5:
			month = malloc(6 * sizeof(char));
			mon = "June";
			break;
		case 6:
			month = malloc(8 * sizeof(char));
			mon = "July";
			break;
		case 7:
			month = malloc(6 * sizeof(char));
			mon = "August";
			break;
		case 8:
			month = malloc(6 * sizeof(char));
			mon = "September";
			break;
		case 9:
			month = malloc(7 * sizeof(char));
			mon = "October";
			break;
		case 10:
			month = malloc(9 * sizeof(char));
			mon = "November";
			break;
		case 11:
			month = malloc(8 * sizeof(char));
			mon = "December";
			break;

	}

	free(month);
}

int main(int argc, char* argv[])
{

	return 0;
}
