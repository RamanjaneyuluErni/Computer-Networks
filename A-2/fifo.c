#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
  int fd;
  char* myfifo="/home/anjierni97/Desktop/CN/myfifo";
  int c=mkfifo(myfifo,0666);
  
  while(1)
  {
        char read1[100],write1[100];
  	fd=open(myfifo,O_WRONLY);
  	fgets(write1,100,stdin);
  	write(fd,write1,strlen(write1)+1);
  	close(fd);

  	fd=open(myfifo,O_RDONLY);
  	read(fd,read1,100);
  	printf("%s\n",read1);
  	close(fd);
  }
  return 0;
}
