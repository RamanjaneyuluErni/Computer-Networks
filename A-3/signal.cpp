#include <bits/stdc++.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;
int pid,cpid,fd;
void p2c(int  sig)
{
  cout<<"parent signalled child "<<sig<<endl;
  sleep(2);
  //kill(pid,SIGUSR1);
  
}
void c2p(int sig)
{
  cout<<"child signalled parent"<<sig<<endl;
  sleep(2);
  //kill(cpid,SIGUSR2);
  
}
int main()
{
    signal(SIGUSR1,c2p);
    signal(SIGUSR2,p2c);
    int c=fork();
    if(c>0)
    {
       cout<<"Parent process started!!  ID:"<<getpid()<<endl;
       cpid=c;
       sleep(4);
       kill(cpid,SIGUSR2);
       while(1);
    }
    else
    {
      cout<<"Child process started! ID:"<<getpid()<<endl;
      int pid=getppid();
      kill(pid,SIGUSR1);
      while(1);
    }
    return 0;
}
