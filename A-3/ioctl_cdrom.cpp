#include <iostream>
#include <sys/ioctl.h>
#include <linux/cdrom.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
using namespace std;
int main()
{
  int fd=open("/dev/cdrom",O_NONBLOCK);
  int i=ioctl(fd,CDROMEJECT);
  if(i==0)
    cout<<"Opened successfully..!!\n";
  else
    cout<<errno<<" Failed to open..\n";

  
  close(fd);

}