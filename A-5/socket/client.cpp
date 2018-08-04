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
	int* csfd = (int*)p; 
	while(true)
	{
		char buffer[100] = {};
		read(csfd[0], buffer, sizeof(buffer));
		cout<<"\t\t\t\t"<<buffer<<endl;
	}
}

void* tsend(void* p)
{
	int* csfd = (int*)p;
	while(true)
	{
		char buffer[100] = {};
		cin.getline(buffer,100);
		send(csfd[0], buffer, strlen(buffer), 0);
	}
}

int main()
{
    
    int client_sfd;

    client_sfd = socket(domain, TYPE, 0);
    if(client_sfd < 0)
    {
    	cout<<"Error in socket\n";
    	return -1;
    }

    struct sockaddr_in address;
    address.sin_family = domain;
    address.sin_port = htons(PORT);

    if(inet_pton(domain, "127.0.0.1", &address.sin_addr) < 0)
    {
    	cout<<"address not supported\n";
    	return -1;
    } 

    if(connect(client_sfd, (struct sockaddr*)&address, sizeof(address)) < 0)
	{
		cout<<"Connection Failed\n";
		return 0;
	}
    
    int a[1] = {};
    a[0] = client_sfd;
	pthread_t t1,t2;
    pthread_create(&t1,NULL,tread,a);
    pthread_create(&t2,NULL,tsend,a);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
	return 0;
}