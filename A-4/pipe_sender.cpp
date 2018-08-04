// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;
 
int main()
{
    int fd;


    char  myfifo[30];
        cout<<"Enter pipe name to send:";
        fgets(myfifo, 30, stdin);
        myfifo[strlen(myfifo)-1] = '\0';
 
    mkfifo(myfifo, 0666);
    
    while (1)
    {
        
        
 
    char arr2[80];

        fd = open(myfifo, O_WRONLY);
 

        fgets(arr2, 80, stdin);
        arr2[strlen(arr2)] = '\0';
 
        write(fd, arr2, strlen(arr2)+1);
        close(fd);

    }
    return 0;
}