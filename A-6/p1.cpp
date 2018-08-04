#include <bits/stdc++.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/poll.h>
using namespace std;
int main()
{
	char buffer[100]; 
	int fd1, fd2, fd3, fd4, fd5;
	//cout<<"hello";
	fd1 = fileno(popen("./p2", "r"));
	fd2 = fileno(popen("./p3", "r"));
	fd3 = fileno(popen("./p4", "r"));
        //cout<<"hi";
	struct pollfd fds[4];
	fds[0].fd = fd1;
	fds[0].events = POLLIN;
	fds[1].fd = fd2;
	fds[1].events = POLLIN;
	fds[2].fd = fd3;
	fds[2].events = POLLIN;

	while(true)
	{
		poll(fds, 3, 2000);
		if (fds[0].revents == POLLIN)
		{
			cout<<"selected1";
			fd5 = fileno(popen("./p5", "w"));
			dup2(fd1, 0);
			cin>>buffer;
			dup2(fd5, 1);
			cout<<buffer;
			close(fd5);

		}

		if (fds[1].revents == POLLIN)
		{
			cout<<"selected2";
			fd5 = fileno(popen("./p5", "w"));
			dup2(fd2, 0);
			cin>>buffer;
			dup2(fd5, 1);
			cout<<buffer;
			close(fd5);
		}

		if (fds[2].revents == POLLIN)
		{
			cout<<"selected3";
			fd5 = fileno(popen("./p5", "w"));
			dup2(fd3, 0);
			cin>>buffer;
			dup2(fd5, 1);
			cout<<buffer;
			close(fd5);
		}
		else
		{
			cout<<"selected4";
			fd5 = fileno(popen("./p5", "w"));
			cin>>buffer;
			dup2(fd5, 1);
			cout<<buffer;
			close(fd5);
		}
	}
	return 0;
}
