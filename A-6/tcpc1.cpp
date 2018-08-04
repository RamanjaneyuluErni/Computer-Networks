#include <sys/socket.h>
#include<arpa/inet.h>
#include<bits/stdc++.h>
#define PORT 8080
using namespace std; 
int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char hello[1024];
    char buffer[1024];
	sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    cin.getline(hello,1024);
    send(sock , hello , strlen(hello)+1 , 0 );
    cout<<"msg sent\n";
    valread =recv( sock , buffer, 1024,0);
    cout<<buffer<<"\n";
    return 0;
}
