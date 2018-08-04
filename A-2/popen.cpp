#include <bits/stdc++.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
using namespace std;
int main()
{
    FILE* file_pointer;
    int n;
    string str;
    cout<<"Enter no of processes to create :";
    cin>>n;
    cout<<"Enter some message here "<<n<<". It's ID is "<<getpid()<<endl;
    cin>>str;
    file_pointer=popen("./popen1","w"); 
    if(!file_pointer) 
    {
    	cout<<"failed to open\n";
    	return 0;
    }
    else
    {
    	int fd=fileno(file_pointer);
    	dup2(fd,1);
        cout<<n-1<<" ";
        cout<<str;
    }
	return 0;
}