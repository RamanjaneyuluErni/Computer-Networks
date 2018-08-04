#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;
char n;
void* read(void* f)
{
  char* cfifo=(char*)f;
  while(true)
  {
    char str[100];
    int cd=open(cfifo,O_RDONLY);
    read(cd,str,sizeof(str));
    cout<<"\t\t\t\t\t "<<str<<endl;
    close(cd);  
  }
  
}
void* write(void* f)
{
  char* sfifo=(char*)f;
  while(true)
  {
    char str[100];
    int length;
    cin.getline(str,100);
    length=strlen(str);
    if(length>0)
    {
      str[length]=n;
      str[length+1]='\0';
    }
    int cd=open(sfifo,O_WRONLY);
    write(cd,str,strlen(str)+1);
    close(cd);  
  }
  
}
int main()
{
  cout<<"Enter Client Number : ";
  cin>>n;cin.ignore();
  char cfifo[]="/home/anjierni97/Desktop/CN/Groupchat/cfifo";
  char* sfifo="/home/anjierni97/Desktop/CN/Groupchat/sfifo";
  int x=strlen(cfifo);
  cfifo[x]=n;
  cfifo[x+1]='\0';
  int c=mkfifo(cfifo,0666);

  char s[100],cpath[100];
  cout<<"Enter Groups to join : ";
  string data;
  getline(cin,data);
  strcpy(s,data.c_str());
  strcpy(cpath,cfifo);
  strcat(cpath," ");
  strcat(cpath,s);
  int fd=open(sfifo,O_WRONLY);
  write(fd,cpath,strlen(cpath)+1);
  close(fd);
  //cout<<cpath<<endl;
  pthread_t t1,t2;
  pthread_create(&t1,NULL,read,cfifo);
  pthread_create(&t2,NULL,write,sfifo);
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  return 0;
}
