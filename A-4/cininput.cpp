#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <bits/stdc++.h>
using namespace std;
int main()
{  

  FILE *output;
  output = popen("./server", "w");
  if(!output)return 0;
  int fd=fileno(output);
  int out = dup(1);
  while(1){
    char inp[50];
    fgets(inp,50,stdin);inp[strlen(inp)-1]='\0';
    //cout<<strlen(inp)<<endl;
    //int a;cin>>a;
    dup2(fd,1);
    cout<<inp;
    
    cout<<endl;
  }

   return 0;
}
