#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
void parent_Process(int fd1,int fd2)
{
  char msg1[]="Hello World Cheers!!";
  char msg2[100];
  write(fd1,msg1,strlen(msg1));
  read(fd2,msg2,100);
  printf("%s\n",msg2);
}
void child_Process(int fd1,int fd2)
{
  char msg1[100];
  read(fd1,msg1,sizeof(msg1));
  int i=0;
  while(msg1[i])
  {
     if(msg1[i]>='a' && msg1[i]<='z') msg1[i]-=32;
     i++;
  }
  write(fd2,msg1,100);
}
int main()
{
  int fd1[2],fd2[2],c;
  if(pipe(fd1)==-1)
   {
     printf("pipe1 is failed to open\n");
     return 1;
   }
  if(pipe(fd2)==-1)
  {
    printf("pipe2 is failed to open");
    return 1;
  }
  c=fork();
  if(c>0)
  {
     //parent process
     close(fd1[0]);
     close(fd2[1]);
     parent_Process(fd1[1],fd2[0]);
  }
  else 
  {
     //child process
     close(fd1[1]);
     close(fd2[0]);
     child_Process(fd1[0],fd2[1]);
  }
  return 0;
}
