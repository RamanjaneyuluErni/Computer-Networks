#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;

int pid;

string to_string(int num){
	stringstream ss;
	ss<<num;
	return ss.str();
}

void* getmsg(void *args){
	
	string pipe_name = "/tmp/pipe_" + to_string(pid);
	mkfifo(pipe_name.c_str(),0666);
	int fd;
	while(1){
		fd = open(pipe_name.c_str(),O_RDONLY);
		char msg[100];
		read(fd,msg,100);
		cout<<msg<<endl;
		close(fd);
	}
}


void *putmsg(void *args){

	mkfifo("/tmp/t1",0666);
	mkfifo("/tmp/t2",0666);
	
	while(1){
		cout<<"Enter type:";int type;cin>>type;
		if(type==1){
			int fd = open("/tmp/t1",O_WRONLY);
	    	string msg = to_string(pid);
	    	write(fd,msg.c_str(),msg.length()+1);
	    	close(fd);
		}
		else if(type==2){
	    	cout<<"Enter Process to serve(s1|s2|s3):\n";
			string txt;cin>>txt;
		    string msg=to_string(pid);
		    msg+="|";msg+=txt;
		    int fd = open("/tmp/t2",O_WRONLY); 
		    write(fd,msg.c_str(),msg.length()+1);
		    close(fd);
		}
		sleep(2);
	}

}


int main(){

	pid = getpid();
	cout<<"Client-Id: "<<pid<<endl;
	pthread_t tid0,tid1;sleep(0.5);

    pthread_create(&tid0, NULL, getmsg, NULL);
    

    pthread_create(&tid1, NULL, putmsg, NULL);
   
    pthread_join(tid1, NULL);

    pthread_join(tid0, NULL);

    

	return 0;
}
