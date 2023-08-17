#include<cmath>
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
int n,m,T,l,date[500500],ans[50050];
signed main()
{
	cin>>n>>m>>T;
	for(int i=1;i<=n;i++) 
		cin>>date[i],date[i+n]=date[i];
	for(int i=1;i<=n;i++) 
		if(date[i]==m){l=i;break;}
	for(int i=1;i<=n;i++)
		ans[date[i]]=date[l+(T+n-i)%n];
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
	return 0;
}