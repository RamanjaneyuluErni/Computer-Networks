#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;
#define PORT1 8080
#define PORT2 8082 
#define domain AF_INET
#define TYPE SOCK_STREAM

int main()
{
    
    int client_sfd;

    client_sfd = socket(domain, TYPE, 0);
    if(client_sfd < 0)
    {
    	cout<<"Error in socket\n";
    	return -1;
    }
    
    int num;
    cout<<"Enter server to connect(1 or 2) : ";
    cin>>num;
    cin.ignore();
    struct sockaddr_in address;
    memset(&address, '0', sizeof(address));
    address.sin_family = domain;
    
    if(num == 1) address.sin_port = htons(PORT1);
    else if(num == 2) address.sin_port = htons(PORT2);

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
   
    char buffer[100] = {};
    cin.getline(buffer,100);
    send(client_sfd, buffer, strlen(buffer), 0);
    cout<<"Message sent\n";
    read(client_sfd, buffer, sizeof(buffer));
    cout<<buffer<<endl;
	return 0;
}