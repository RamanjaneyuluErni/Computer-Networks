// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include<iostream>
using namespace std;
 
int main()
{
    int fd;

    char  myfifo[20];
        cout<<"Enter pipename to recive:";
        fgets(myfifo, 20, stdin);
        myfifo[strlen(myfifo)-1] = '\0';
    
    while (1)
    {



        
        mkfifo(myfifo, 0666);
        char arr1[80];

 
        fd = open(myfifo, O_RDONLY);
 
        read(fd, arr1, sizeof(arr1));
 
        printf("%s\n", arr1);
        close(fd);
    }
    return 0;
}