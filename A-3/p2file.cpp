#include <bits/stdc++.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;
int fd,pid,cpid; //pid -> parent process id
void signal_handler2(int sig)
{
    cout<<"Read by process-2\n";
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
    if(buffer[0]!='\0') kill(pid,SIGUSR1);
}
int main(int argc,char* argv[])
{
	char ch1[10],ch2[10];
    strcpy(ch1,argv[1]);
    strcpy(ch2,argv[2]);
   	fd=atoi(ch1);
	pid=atoi(ch2);
    signal(SIGUSR2,signal_handler2);
    // kill(pid,SIGUSR1); 
    while(1);
	return 0;
}
