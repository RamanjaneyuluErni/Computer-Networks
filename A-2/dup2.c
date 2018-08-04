#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
int main()
{
    int fd,fd1;
    char msg1[]="This line is written by fd\n";
    char msg2[]="This line is written by fd1\n";
    char msg3[]="This line is written by fd created by dup2() system call\n";
    fd=open("dupfile.txt",O_WRONLY|O_APPEND|O_TRUNC);
    fd1=dup(fd);
    printf("Screen\n");
    write(fd,msg1,strlen(msg1));
    write(fd1,msg2,strlen(msg2));
    dup2(fd1,1);
    //write(1,msg3,strlen(msg3));
    printf("hello\n");
    printf("hi\n");
	return 0;
}
