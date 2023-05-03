#include <bits/stdc++.h>

using namespace std;

//#define int long long
#define pii pair<int,int>

const int mod=1e9+7;

inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
queue<pii>q;
int dx[]={0,1,1,2,2,-1,-1,-2,-2},dy[]={0,2,-2,1,-1,2,-2,1,-1};
map<pii,int>mp;
int x2,y2;
inline void bfs1(int x,int y){
	q.push({x,y});
	mp[{x,y}]=0;
	while(q.size()){
		pii u=q.front();q.pop();
		int ux=u.first,uy=u.second;
		for(int i=1,tx,ty;i<=8;i++){
			tx=ux+dx[i];ty=uy+dy[i];
			if(mp[{tx,ty}]!=0)continue;
			mp[{tx,ty}]=mp[u]+1;
			if(tx==x2&&ty==y2){
				cout<<mp[{tx,ty}]<<endl;
				return;
			}
			q.push({tx,ty});
		}
	}
}
signed main(){
	freopen("horse.in","r",stdin);
    freopen("horse.out","w",stdout);
    int x1=read(),y1=read();x2=read(),y2=read();
	int l=abs(x2-x1),r=abs(y1-y2);
    int len=max(l,r);
    int dis=l+r;
    if(dis<=60){
        bfs1(x1,y1);
        return 0;
    }
    double t=ceil((double)len/2)+1;
    if(dis%2==1){
        int r1=(dis+3)/2;
        int l1=ceil(dis/3);
        int lmin=len/2+1;
        //cout<<l1<<" "<<r1<<endl;
        for(int i =l1;i<=r1;i++){
            if(dis>=2*i-3&&dis<=i*3&&2*i>=len&&len>=i-1&&i%2==1){
                cout<<i<<endl;
                return 0;
            }
        }
    }
    if(dis%2==0){
        int r1=(dis+2)/2;
        int l1=ceil(dis/3);
        int lmin=len/2;
        for(int i =l1;i<=r1;i++){
            if(dis>=2*i-2&&dis<=i*3&&2*i>=len&&len>=i-1&&i%2==0){
                cout<<i<<endl;
                return 0;
            }
        }
    }
	return ~~(0-0);
}