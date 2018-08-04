#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;
 
int main(int argc, char const *argv[])
{

    int fd;
    string myfifo = "/tmp/pipe_" + string(argv[1]);
    cout<<myfifo;
 
    mkfifo(myfifo.c_str(), 0666);
    fd = open(myfifo.c_str(), O_WRONLY);
    string msg = "Received data from s3\n";
    write(fd, msg.c_str(), msg.length()+1);
    close(fd);
    return 0;
} 