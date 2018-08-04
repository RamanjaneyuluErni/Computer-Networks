#include<bits/stdc++.h>
#include <sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;
int main()
{
char buffer[1024];
char *hello="msg from server";
int valread = recv( 5, buffer, 1024,0);
cout<<"child handled client : "<<buffer<<"\n";
send(5 ,"from child",11, 0 );
return 0;
}
