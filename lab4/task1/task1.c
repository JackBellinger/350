
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int convIntToStr(char * str, int x)
{
  sprintf(str, "%d", x);
  return strlen(str);
}

int convStrToInt(char num[])
{
    int n=0;
    int len = strlen(num);
    for(int i=0; i<len; i++)
    {
        n =n * 10 +  (num[i] - '0');
    }
    return n;
}

int main(int argc, char * argv[])
{
  int InFileDes;
  char c;
  char digits[80];
  int i = 0;
  umask(0);

  InFileDes = open(argv[1], O_RDONLY);

  while(read(InFileDes, &c, 1) ==1)
  {
    if(isdigit(c) > 0)
    {
      digits[i++] = c;
    }
  }
  
  int num = convStrToInt(digits) + 10;
  
  int len = convIntToStr(digits, num);

  write(1, digits, len );
  printf("\n");
	
  
  
  

}
