#include <bits/stdc++.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
using namespace std;
int* shm_array;
void signal_handler1(int sig) 
{
    cout<<"Running process-1 :";
    int temp=shm_array[2];
    temp++;
    shm_array[3]=temp;
    cout<<"y value is "<<shm_array[3]<<endl;
    sleep(2);
    kill(shm_array[1],SIGUSR2);
}
int main(int argc,char* argv[])
{
    size_t size;
    key_t myKey;
    int shmid,pid;
    pid=getpid();
    size=4*sizeof(int);
    myKey=ftok("/home/anjierni97/Desktop",'x');
    shmid=shmget(myKey,size,IPC_CREAT|0666);
    shm_array=(int*)shmat(shmid,NULL,0);
    shm_array[0]=pid;
    shm_array[2]=0; // X value
    shm_array[3]=0; // Y value
    signal(SIGUSR1,signal_handler1);
    while(1);
    return 0;
}
