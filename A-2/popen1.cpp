#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
using namespace std;
int main()
{
    FILE* file_pointer;
    int n;
    string str;
    cin>>n;
    cout<<"You are in process "<<n<<" . It's Id is "<<getpid()<<endl;
    cin>>str;
    if(n==1)
    {
        cout<<str<<endl;
        return 0;
    }
    file_pointer=popen("./popen1","w"); 
    int fd=fileno(file_pointer);
    dup2(fd,1);
    cout<<n-1<<" ";
    cout<<str;
    return 0;
}