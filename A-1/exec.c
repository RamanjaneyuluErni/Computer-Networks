#include<stdio.h>
#include<unistd.h>
int main()
{
  char *args[]={"./p4",NULL};
  printf("Now in exec \n");
  printf("shifting to p4\n");
  execvp(args[0],args);
  return 0;
}
