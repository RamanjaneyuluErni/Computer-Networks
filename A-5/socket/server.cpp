#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h> 
using namespace std;
#define PORT 8080
#define domain AF_INET
#define TYPE SOCK_STREAM

void* tread(void* p)
{
	int* nsfd = (int*)p;
	while(true)
	{
		char buffer[100] = {};
		read(nsfd[0], buffer,sizeof(buffer));
		cout<<"\t\t\t\t"<<buffer<<endl;
	}
}

void* tsend(void* p)
{
	int* nsfd = (int*)p;
	while(true)
	{
		char buffer[100] = {};
		cin.getline(buffer,100);
		send(nsfd[0], buffer, strlen(buffer), 0); 
	}
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
    
    cout<<"before accept\n";
    if((nsfd = accept(server_sfd, (struct sockaddr *)&address, (socklen_t*)&addrlen )) < 0)
    {
    	cout<<"Accept failure\n";
    	exit(EXIT_FAILURE);
    }
    cout<<"request accepted\n";
    int  a[1] = {};
    a[0] = nsfd;
    pthread_t t1,t2;
    pthread_create(&t1,NULL,tread,a);
    pthread_create(&t2,NULL,tsend,a);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
	return 0;
}