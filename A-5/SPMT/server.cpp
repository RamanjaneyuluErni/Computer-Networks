 #include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
using namespace std;
#define PORT 8080
#define domain AF_INET
#define TYPE SOCK_STREAM

void* fun(void* p)
{ 
	int* sfd = (int*)p;
    char buffer[100] = {};
    read(sfd[0], buffer, sizeof(buffer));
    for(int i=0;i<strlen(buffer);i++)
    {
        buffer[i] = toupper(buffer[i]);
    }
    send(sfd[0], buffer, strlen(buffer), 0);
}
int main()
{
    int server_sfd, nsfd;
    int opt = 1;
    server_sfd=socket (domain, TYPE, 0);
    if(server_sfd < 0) 
    {
    	cout<<"Socket failed\n";
    	exit(EXIT_FAILURE);
    }
    if(setsockopt(server_sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)) < 0)
    {
        cout<<"Error in setsockopt \n";
        exit(EXIT_FAILURE);
    }
 
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = domain;
    address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if(bind(server_sfd, (struct sockaddr*)&address ,sizeof(address)) < 0)
	{
		cout<<"Failed in binding\n";
		exit(EXIT_FAILURE); 
	}
	if(listen(server_sfd, 5) < 0) 
	{
		cout<<"Error in listen system call\n";
		exit(EXIT_FAILURE);
	}
    while(true)
    {
        cout<<"before accept\n";
        if((nsfd = accept(server_sfd, (struct sockaddr *)&address, (socklen_t*)&addrlen )) < 0)
        {
          cout<<"Accept failure\n";
          exit(EXIT_FAILURE);
        }
        cout<<"request accepted\n";
        int c = fork();
        if(c>0)
        {
            close(nsfd);
        }
        else
        {

          close(server_sfd);
          int fd[1] = {};
          fd[0] = nsfd;
          pthread_t t;
          pthread_create(&t,NULL,fun,fd);
          pthread_join(t,NULL);
        }

    }
    
	return 0;
}