#include <bits/stdc++.h>
using namespace std;

int main()
{
	string crc_gen,str,str1;
	int l1,l2;
	cout<<"Enter CRC_Generator\n";
	cin>>crc_gen;
    cout<<"Enter message(Binary Encrypted)\n";
    cin>>str;
    str1 = str;
    l2 = crc_gen.length();
    for(int i=1;i<l2;i++) str1+='0';
    l1 = str1.length();
    cout<<str1<<endl;
    int rlen=l1,j=0;
    while(l2<=rlen)
    {
      for(int i=j,k=0;k<l2;i++,k++)
      {
      	int a,b;
      	a = crc_gen[k]-'0';
        b = str1[i]-'0';
      	str1[i] = (a^b) + '0';
      }
      while(str1[j]!='1') j++;
      rlen = l1-j;
    }
    for(int i=1;i<l2;i++) str+=str1[l1-l2+i];
    cout<<"Final Message : "<<str<<endl;
	return 0;
}