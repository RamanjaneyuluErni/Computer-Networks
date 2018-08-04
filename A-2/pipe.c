#include<stdio.h>
#include<unistd.h>
#include<string.h>
void parent_Process(int fd)
{
  char msg[]="Hello World Cheers!!";
  write(fd,msg,strlen(msg)+1);
}
void child_Process(int fd)
{
  char m[100];
  read(fd,m,sizeof(m));
  printf("%s\n",m);
}
int main()
{
  int fd[2],c;
  if(pipe(fd)==1)
   {
     printf("pipe failed\n");
     return 1;
   }
  c=fork();
  if(c>0)
  {
     //parent process
     close(fd[0]);
     parent_Process(fd[1]);
  }
  else 
  {
     //child process
     close(fd[1]);
     child_Process(fd[0]);
  }
  return 0;
}
