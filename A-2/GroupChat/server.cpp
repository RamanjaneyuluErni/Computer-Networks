#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;
map<string,vector<string> > groups;
int main()
{
  char* fifo="/home/anjierni97/Desktop/CN/Groupchat/sfifo";
  int c=mkfifo(fifo,0666);
  while(true)
  {
    char msg[100];
    int cd,i=0;
    cd=open(fifo,O_RDONLY);
    read(cd,msg,sizeof(msg));
    close(cd);
    if(msg[0]=='/')
    {
      char *tok=strtok(msg," ");
      int i=0;char client;
      string mypath;
      while(tok)
      {
        string wd="";int j=0;
        while(tok[j])
        {
          wd+=tok[j];j++;
        }
        if(i==0)
        {
          mypath=wd;
          client=wd[wd.length()-1];
          cout<<"Access Granted\n";
        }
        else 
        {
          groups[wd].push_back(mypath);
          cout<<"Client "<<client<<" Joined in group-"<<wd<<endl;
        }
        tok=strtok(NULL," ");
        i++;
      }    
    }
    else if(msg[0]!='\0')
    {
      int len=strlen(msg);
      char gr=msg[len-2],client=msg[len-1];
      cout<<"Message recieved(client-"<<client<<" group-"<<gr<<": "<<msg<<endl;
      string str;
      str+=gr;
      vector<string> v=groups[str];

      for(int i=0;i<v.size();i++)
      {
        string tmp=v[i];
        if(tmp[tmp.length()-1]!=client)
        {
          char arr[100];
          strcpy(arr,tmp.c_str());
          int fd=open(arr,O_WRONLY);
          write(fd,msg,strlen(msg)+1);
          close(fd);
        }
      }
    }
  }
  return 0;
}
