#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
  int data_processed, nchar;
  char buffer[BUFSIZ+1];
  const char some_data[] = "Hi Mom";
  int file_descriptor;
  int write_descriptor;

  memset(buffer, '\0', sizeof(buffer));
  sscanf(argv[1], "%d", &file_descriptor);
  sscanf(argv[2], "%d", &write_descriptor);
  data_processed=read(file_descriptor, buffer,BUFSIZ);
  nchar=write(write_descriptor, some_data,BUFSIZ);
  close(file_descriptor);
  printf("Child:%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
  printf("Child:%d - wrote %d bytes \n", getpid(), nchar);
  exit(EXIT_SUCCESS);
}
