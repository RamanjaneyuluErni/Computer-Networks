#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h> 
#include <sys/select.h>
using namespace std; 
#define PORT1 8080
#define PORT2 8082 
#define domain AF_INET
#define TYPE SOCK_STREAM

void* fun1(void* p)
{ 
    char buffer[100] = {};
    read(0, buffer, sizeof(buffer));
    for(int i=0;i<strlen(buffer);i++)
    {
        buffer[i] = toupper(buffer[i]);
    }
    send(0, buffer, strlen(buffer), 0);
}

void* fun2(void* p)
{ 
    char buffer[100] = {};
    read(0, buffer, sizeof(buffer));
    for(int i=0;i<strlen(buffer);i++)
    {
        buffer[i] = tolower(buffer[i]);
    }
    send(0, buffer, strlen(buffer), 0);
}
int main()
{
    int sfd1,sfd2;
    int opt = 1;
    struct sockaddr_in address1,address2;
    int addrlen1 = sizeof(address1);
    int addrlen2 = sizeof(address2);
    //memset(&address1, '0', sizeof(address1));
    //memset(&address2, '0', sizeof(address2));

    sfd1 = socket(domain, TYPE, 0);
    if(sfd1 < 0)
    {
    	cout<<"Error in socket1\n";
    	exit(EXIT_FAILURE);
    }

    if(setsockopt(sfd1, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)) < 0)
    {
        cout<<"Error in setsockopt1 \n";
        exit(EXIT_FAILURE);
    }

   
    address1.sin_family = domain;
    address1.sin_addr.s_addr = INADDR_ANY;
	address1.sin_port = htons(PORT1);

    if(bind(sfd1, (struct sockaddr*)&address1 ,sizeof(address1)) < 0)
	{
		cout<<"Failed in binding1\n";
		exit(EXIT_FAILURE); 
	}

	if(listen(sfd1, 5) < 0)
	{
		cout<<"Error in listen1 system call\n";
		exit(EXIT_FAILURE);
	}

    sfd2 = socket(domain, TYPE, 0);
    if(sfd2 < 0)
    {
    	cout<<"Error in socket2\n";
    	exit(EXIT_FAILURE);
    }

    if(setsockopt(sfd2, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)) < 0)
    {
        cout<<"Error in setsockopt2 \n";
        exit(EXIT_FAILURE);
    }

    address2.sin_family = domain;
    address2.sin_addr.s_addr = INADDR_ANY;
	address2.sin_port = htons(PORT2);
   
    if(bind(sfd2, (struct sockaddr*)&address2 ,sizeof(address2)) < 0)
	{
		cout<<"Failed in binding2\n";
		exit(EXIT_FAILURE); 
	} 

	if(listen(sfd2, 5) < 0)
	{
		cout<<"Error in listen2 system call\n";
		exit(EXIT_FAILURE);
	}
    
    struct timeval tval;
    tval.tv_sec = 2;
    tval.tv_usec = 0;
    while(true)
    {
    	fd_set readfds;
    	FD_ZERO(&readfds);
    	FD_SET(sfd1, &readfds);
    	FD_SET(sfd2, &readfds);
       
        cout<<"hi\n";
    	int val = select(100, &readfds, NULL, NULL, NULL);
        cout<<"hello\n";
        if(FD_ISSET(sfd1, &readfds))
        {

             int nsfd1;cout<<"s1\n";
             if((nsfd1 = accept(sfd1, (struct sockaddr *)&address1, (socklen_t*)&addrlen1 )) < 0)
             {
                cout<<"Accept failure\n";
                exit(EXIT_FAILURE);
             }
             cout<<"request accepted\n";
             int c = fork();
             if(c>0) close(nsfd1);
             else
             {

               dup2(nsfd1, 0);
               close(sfd1);
               pthread_t t;
               pthread_create(&t,NULL,fun1,NULL);
               pthread_join(t,NULL);
             }
        }
        else if(FD_ISSET(sfd2, &readfds))
        {
            int nsfd2;
             if((nsfd2 = accept(sfd2, (struct sockaddr *)&address2, (socklen_t*)&addrlen2 )) < 0)
             {
                cout<<"Accept failure\n";
                exit(EXIT_FAILURE);
             }
             cout<<"request accepted\n";
             int c = fork();
             if(c>0) close(nsfd2);
             else
             {
               dup2(nsfd2, 0);
               close(sfd2);
               pthread_t t;
               pthread_create(&t,NULL,fun2,NULL);
               pthread_join(t,NULL);
             }
        }
    }
 	return 0;
}