#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,low,hi,l[1500],m[1500],suml[1500],summ[1500],f[1300][1300];
signed main(){
	n=read();low=read();hi=read();
	for(int i=1;i<=n;i++){
		l[i]=read();
		suml[i]=suml[i-1]+l[i];	
	}
	for(int i=1;i<=n;i++){
		m[i]=read();
		summ[i]=summ[i-1]+m[i];	
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			int len=suml[j]-suml[i-1];
			f[i][j]=max(f[i-1][j],f[i][j-1]);
			if(len>=low&&len<=hi){
				f[i][j]=max(f[i][j],f[i-1][j-1]+summ[j]-summ[i-1]);
			}
		}
	}
	cout<<f[n][n]<<"\n";
    return 0;
}