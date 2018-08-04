#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>
#include <pthread.h>
using namespace std;

string to_string(int num){
	stringstream ss;
	ss<<num;
	return ss.str();
}

void *serve(void* arg){
	
	int *sender = (int *)arg;
	string pipe_name = "/tmp/pipe_" + to_string(sender[0]);
	int fd;
	fd = open(pipe_name.c_str(),O_WRONLY);
	string msg = "Received data from server\n";
	write(fd,msg.c_str(),msg.length()+1);
	close(fd);

}


int main()
{
	
	mkfifo("/tmp/t1",0666);mkfifo("/tmp/t2",0666);
	int fd1;
	fd1 = open("/tmp/t1",O_RDWR);
	int fd2;
	fd2 = open("/tmp/t2",O_RDWR);
	
	
	pthread_t tid[100];int idc=0;
	
	sleep(0.5);
    fd_set read_fds;
	struct timeval timeout;
	
	while(1){
		
		FD_ZERO(&read_fds);
		FD_SET(fd1,&read_fds);
		FD_SET(fd2,&read_fds);
		timeout.tv_sec = 2;
    	timeout.tv_usec=0;
		int ret = select(max(fd1,fd2)+1,&read_fds,NULL,NULL,NULL);
		if(ret==-1)cout<<"select error\n";
		else if(ret){
			if(FD_ISSET(fd1,&read_fds)){

				char buf[50];
				read(fd1,buf,50);
				int sender[1];sender[0] = atoi(buf);

				pthread_create(&tid[idc],NULL,serve,(void*)sender);
				pthread_join(tid[idc],NULL);idc++;

			}

			if(FD_ISSET(fd2,&read_fds)){
				char buf[50];
				read(fd2,buf,50);
				string str = string(buf);
				int sender = atoi(str.substr(0,str.find('|')).c_str());
				string message = str.substr(str.find('|')+1, str.size() - str.find('|'));
				string path = "./" + message;
				int a = fork();
				if(a<0)return 0;
				else if(a==0)
					execlp(path.c_str(),message.c_str(),str.substr(0,str.find('|')).c_str(),NULL);
			}
		}
		else{
			cout<<"Nothing is read\n";
		}
	
	}

	return 0;
}