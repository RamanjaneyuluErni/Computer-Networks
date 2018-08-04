#include <bits/stdc++.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
using namespace std;
int* shm_array;
void signal_handler2(int sig)
{
    cout<<"Running process-2 :";
    int temp=shm_array[3];
    temp++;
    shm_array[2]=temp;
    cout<<"x value is "<<shm_array[2]<<endl;
    sleep(2);
    kill(shm_array[0],SIGUSR1);
}
int main(int argc,char* argv[])
{   
    size_t size;
    key_t myKey;
    int shmid,pid;
    pid=getpid();
    size=4*sizeof(int);
    myKey=ftok("/home/anjierni97/Desktop",'x');
    shmid=shmget(myKey,size,0666);
    shm_array=(int*)shmat(shmid,NULL,0);
    shm_array[1]=pid;
    signal(SIGUSR2,signal_handler2);
    kill(shm_array[0],SIGUSR1);
    while(1);
  return 0;
}