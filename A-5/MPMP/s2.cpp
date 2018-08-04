#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;
int main() 
{
    char buffer[100] = {};
    read(0, buffer, sizeof(buffer));
    for(int i=0;i<strlen(buffer);i++)
    {
        buffer[i] = tolower(buffer[i]);
    }
    send(0, buffer, strlen(buffer), 0);
	return 0;
}