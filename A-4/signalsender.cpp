#include <bits/stdc++.h>
using namespace std;
int main(){
	cout<<"Enter pid to kill:";pid_t pid;cin>>pid;
	kill(pid,SIGUSR1);
	return 0;
}