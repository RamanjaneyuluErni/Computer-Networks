#include <bits/stdc++.h>
using namespace std;

void print(vector<int >v[], int r)
{
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<v[i].size();j++) cout<<v[i][j]<<" ";
		cout<<endl;
	}
}
int main() 
{
    int m,r;
    string str;
    cout<<"Enter message(Binary encrypted)\n";
    cin>>str;
    cin.ignore();
    m = str.length(); 
    r = floor(log(m)/log(2)) + 1;
    if(pow(2,r) <= m+r+1) r++;
    cout<<r<<" parity bits required"<<endl;
    int msg[m+r+1] = {};
    vector<int> v[r];
    for(int i = 1;i<=r+m;i++)
    {
    	int k = 0,num = i;
    	while(num)
    	{
    		if(num&1) v[k].push_back(i);	
    		k++;
    		num = num>>1; 
    	}
    }
    print(v,r);
    int k=0;
    for(int i = 1;i<m+r+1;i++)
    {
      if(ceil(log2(i)) != floor(log2(i))) msg[i] = str[k++]-'0';
    }
    for(int i = 0;i<r;i++)
    {
      k=0;
      for(int j=0;j<v[i].size();j++) 
      {
      	if(ceil(log2(v[i][j])) != floor(log2(v[i][j]))) k = k^msg[v[i][j]];
      	
      }
      int p = pow(2,i);
      msg[p]=k;
    }
    for(int i=1;i<m+r+1;i++) cout<<msg[i];
    cout<<endl;
	return 0;
}