#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <sys/select.h>
using namespace std;

string to_string(int num){
	stringstream ss;
	ss<<num;
	return ss.str();
}

void hp1(int sig){
	string pipe_name = "/tmp/sigrec";
	mkfifo(pipe_name.c_str(),0666);
	int fd;
	fd = open(pipe_name.c_str(),O_WRONLY);
	string msg = "Received data from signal\n";
	write(fd,msg.c_str(),msg.length()+1);
	close(fd);
}

int main()
{

	int mypipe[2];

	if(pipe(mypipe)){
		cout<<"Failed";return 0;
	}

	int c = fork();
	if(c<0){
		cout<<"Failed fork";return 0;
	}
	else if(c==0){
		//Child
		sleep(5);
		string msg = "Hello from pipe";
		close(mypipe[0]);
		write(mypipe[1],msg.c_str(),msg.length()+1);
		while(1)sleep(1);
		return 0;
	}

	signal(SIGUSR1,hp1);
	cout<<"pid:"<<getpid()<<endl;
    string pipe_name = "/tmp/s1";
	mkfifo(pipe_name.c_str(),0666);
	int fd1 = open(pipe_name.c_str(),O_RDWR);
	int fd2 = 0;
	int fd3 = mypipe[0];
	fd_set read_fds;
	struct timeval timeout;
	
	while(1){

		FD_ZERO(&read_fds);
		FD_SET(fd1,&read_fds);
		FD_SET(fd2,&read_fds);
		FD_SET(fd3,&read_fds);
		timeout.tv_sec = 1;
    	timeout.tv_usec=0;
		int ret = select(FD_SETSIZE,&read_fds,NULL,NULL,NULL);
		if(ret==-1)cout<<"select error\n";
		else if(ret){
			if(FD_ISSET(fd1,&read_fds)){
				char buf[50];
				read(fd1,buf,50);
				int a = fork();
				if(a==0){
					cout<<"fifo input reads:"<<buf<<endl;
					string str = string(buf);
					int sender = atoi(str.substr(0,str.find('|')).c_str());
					string message = str.substr(str.find('|')+1, str.size() - str.find('|'));
					int fd;
				    string myfifo = "/tmp/pipe_" + to_string(sender);
				    fd = open(myfifo.c_str(), O_WRONLY);
				    string msg = "Received data from forked server\n";
				    write(fd, msg.c_str(), msg.length()+1);
				    close(fd);
				}
				
			}

			if(FD_ISSET(fd2,&read_fds)){
				char buf[50];
				read(fd2,buf,50);
				cout<<"cin reads:"<<buf<<endl;

			}

			if(FD_ISSET(fd3,&read_fds)){
				char buf[50];
				close(mypipe[1]);
				read(fd3,buf,50);
				cout<<"parent reads from pipe:"<<buf<<endl;
			}

		}
		else{
			cout<<"Nothing is read\n";
		}
	
	}

	return 0;
}