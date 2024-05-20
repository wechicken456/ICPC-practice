#include<bits/stdc++.h>
using namespace std;int n,i,j;void s(string c,int y,int x){for(i=0 ;i<25;i++){for(j=0 ;j<5;j++,x++){c[5+j%5]++;if(c[5+j%5]>'z')c[5+j%5]='a';
cout<<c<<"\n";if(x+1==n)return;}}if(y%2==0)c[4]++;else c[2]++;x++;cout<<c<<"\n";if(x==n)return;if(y%2==0)c[3]++;else c[1]++;x++;cout<<c<<"\n";if(x==n)return;s(c,y+1,x);}int main(){cin >> n;string a="aaaaaaaaaa";s(a,0,0);}

