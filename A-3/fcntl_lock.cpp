#include <bits/stdc++.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;
int main()
{
    int fd,c;
    fd=open("fcntl_file.txt",O_RDONLY|O_WRONLY|O_TRUNC);
    c=fork();
    if(c>0)
    {
      struct flock lock;
      memset (&lock, 0, sizeof(lock));
      int i=3;
      while(i--)
      {
      	/* acquire lock*/
        lock.l_type=F_WRLCK;
        fcntl(fd,F_SETLKW,&lock);
        cout<<"parent acquired lock,write somthing to file\n";
        char buffer[100];
        cin.ignore();
        cin.getline(buffer,100);
        write(fd,buffer,strlen(buffer)+1); 
        /* release lock*/
        lock.l_type=F_UNLCK;
        fcntl(fd,F_SETLKW,&lock);
        cout<<"Parent released lock\n";
        sleep(2);
      }
    }
    else
    { 
      sleep(2);
      struct flock lock;
      memset (&lock, 0, sizeof(lock));
      int i=3;
      while(i--)
      {
      	/* acquire lock*/
        lock.l_type=F_WRLCK;
        fcntl(fd,F_SETLKW,&lock);
        cout<<"child acquired lock,write somthing to file\n";
        char buffer[100];
        cin.ignore();
        cin.getline(buffer,100);
        write(fd,buffer,strlen(buffer)+1);
        /* release lock*/
        lock.l_type=F_UNLCK;
        fcntl(fd,F_SETLKW,&lock);
        cout<<"child released lock\n";
        sleep(2);
      }
    }
	return 0;
}
