#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <sys/select.h>
using namespace std;

int main()
{
	
    string pipe_name = "/tmp/s1";
	mkfifo(pipe_name.c_str(),0666);
	int fd1 = open(pipe_name.c_str(),O_RDWR);
	pipe_name = "/tmp/s2";
	mkfifo(pipe_name.c_str(),0666);
	int fd2 = open(pipe_name.c_str(),O_RDWR);

	fd_set read_fds;
	
    
	struct timeval timeout;
	
	while(1){

		FD_ZERO(&read_fds);
		FD_SET(fd1,&read_fds);
		FD_SET(fd2,&read_fds);
		timeout.tv_sec = 5;
    	timeout.tv_usec=0;
		int ret = select(FD_SETSIZE,&read_fds,NULL,NULL,&timeout);
		cout<<"Response in "<<timeout.tv_sec<<"seconds\n";
		if(ret==-1)cout<<"select error\n";
		else if(ret){
			cout<<"ret \n";
			if(FD_ISSET(fd1,&read_fds)){
				char buf[50];
				read(fd1,buf,50);
				cout<<"fd1 reads:"<<buf<<endl;
			}

			if(FD_ISSET(fd2,&read_fds)){
				char buf[50];
				read(fd2,buf,50);
				cout<<"fd2 reads:"<<buf<<endl;

			}
		}
		else{
			cout<<"Nothing is read\n";
		}
	
	}

	return 0;
}