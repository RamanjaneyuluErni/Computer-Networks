#include <bits/stdc++.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;
int fd,cpid,pid;
void signal_handler1(int sig)
{
    cout<<"Read by process-1\n";
    char ch[1],buffer[100];
    read(fd,ch,1);
    int i=0;
    while(ch[0]!='\n')
    { 
    	buffer[i]=ch[0];
        read(fd,ch,1);
        i++;
    }
    buffer[i]='\0';
    cout<<buffer<<endl;
    sleep(2);
    if(buffer[0]!='\0') kill(cpid,SIGUSR2);
} 
int main(int argc,char* argv[])
{
    fd=open("file1.txt",O_RDONLY);
    int c=fork();
    if(c>0)
    {
      cout<<"Parent Process started\n";
      cpid=c;
      signal(SIGUSR1,signal_handler1);
      sleep(4);
      kill(cpid,SIGUSR2);
      while(1);
    }
    else
    {
       cout<<"Child process started\n";
       pid=getppid();
       char* arr[4];
       arr[0]="./p2file";
       char ch1[10],ch2[10];
       sprintf(ch1,"%d",fd);
       arr[1]=ch1;
       sprintf(ch2,"%d",pid);
       arr[2]=ch2;
       arr[3]=NULL;
       execvp(arr[0],arr);
    }
	return 0;
}
