#include <sys/socket.h>
#include<arpa/inet.h>
#include<bits/stdc++.h>
#include<unistd.h>
#define PORT 8080
using namespace std;
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    bind(server_fd, (struct sockaddr *)&address,sizeof(address)); 
    listen(server_fd, 3);
    struct sockaddr_in loc_address;
	int loc_len;
	loc_len = sizeof(loc_address);
	getsockname(server_fd, (struct sockaddr *)&loc_address, (socklen_t*)&loc_len);
	cout<<"local IP address is: "<<inet_ntoa(loc_address.sin_addr)<<"\n";
	cout<<"local port is: "<<(int) ntohs(loc_address.sin_port)<<"\n";
    while(1)
    {
    	int nsfd= accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen);
    	dup2(nsfd,5);
        int c=fork();
        if(c>0)
        {	
        	/*cout<<"parent : "<<getpid()<<"\n";
        	char buf[1024];
        	recv(nsfd,buf,1024,0);
        	cout<<"parent handled client : "<<buf<<"\n";
        	send(nsfd,"parent msg",11,0);*/
        	close(nsfd);
        	//shutdown(nsfd,SHUT_RDWR);
        	//shutdown(nsfd,SHUT_RD);
        	//shutdown(nsfd,SHUT_WR);
        }
        if(c==0)
        {
        	struct sockaddr_in peer_address;
			int peer_len;
			peer_len = sizeof(peer_address);
			getpeername(server_fd, (struct sockaddr *)&peer_address, (socklen_t*)&peer_len);
			cout<<"Peer's IP address is: "<<inet_ntoa(peer_address.sin_addr)<<"\n";
			cout<<"Peer's port is: "<<(int) ntohs(peer_address.sin_port)<<"\n";
        	cout<<"child : "<<getpid()<<"\n";
        	close(server_fd);
        	execvp("./service",NULL);
        }
        cout<<"outside while : "<<getpid()<<"\n";
    }
    return 0;
}
