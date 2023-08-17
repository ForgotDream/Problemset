#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
int f[500][500];
inline void init(){
	for(int i=0;i<=9;i++)if(i!=4)f[1][i]=1;
	for(int i=2;i<=22;i++){
		for(int j=0;j<=9;j++){
			for(int k=0;k<=9;k++){
				if(k==4||j==4||k==3&&j==1)continue;
				f[i][j]+=f[i-1][k];	
			}
		}
	}
}
inline int dp(int n){
	if(!n)return 0;
	vector<int>nums;
	while(n)nums.push_back(n%10),n/=10;
	int res=0,last=0;
	for(int i=nums.size()-1;i>=0;i--){
		int x=nums[i];
		for(int j=0;j<x;j++){
			if(j==4||j==3&&last==1)continue;
			res+=f[i+1][j];
		}
		if(x==4||last==1&&x==3||last==4)break;
		last=x;
		if(!i)res++;
	}
	return res;
}
signed main(){
	freopen("height.in","r",stdin);
	freopen("height.out","w",stdout);
	init();
	int T=read();
	int x,y;
	while(T--){
		x=read();y=read();
		printf("%lld\n",(dp(x)-1)*y);
	}
	return 0;
}
