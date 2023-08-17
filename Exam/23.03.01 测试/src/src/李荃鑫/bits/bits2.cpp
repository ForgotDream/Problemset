#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,l;
stack<int>s;
int ans[50][50];
signed main(){
	freopen("out.txt","w",stdout);
	for(int k=30;k<=31;k++){
		for(int l=1;l<=k;l++){
			int x=0;
			for(int i=1;i<=(1<<k)-1;i++){
				int t=__builtin_popcount(i);
				//cout<<t<<endl;
				if(t<=l)x++;
			}
			ans[k][l]=x;
		}
	}
	for(int i=0;i<=31;i++){
		cout<<"{";
		for(int j=0;j<=31;j++){
			cout<<ans[i][j]<<",";
		}
		cout<<"}"<<endl;
	}
	return 0;
}
