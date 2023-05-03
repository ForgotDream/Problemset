#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<queue>
#include<cmath>
#include<map>
#include<queue>
#define mod 1000000007
#define inf 2000000000
#define ll long long 
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int x,y,ans;
int xp,yp,xs,ys;
int xx[8]={1,1,-1,-1,2,2,-2,-2},yy[8]={2,-2,2,-2,1,-1,1,-1};
int dis[105][105];
int qx[10005],qy[10005];
void bfs()
{
	memset(dis,-1,sizeof(dis));
	int head=0,tail=1;
	qx[0]=x;qy[0]=y;dis[x][y]=0;
	while(head!=tail)
	{
		int x=qx[head],y=qy[head];head++;
		for(int k=0;k<8;k++)
		{
			int nowx=x+xx[k],nowy=y+yy[k];
			if(nowx<0||nowy<0||nowx>100||nowy>100)continue;
			if(dis[nowx][nowy]!=-1)continue;
			dis[nowx][nowy]=dis[x][y]+1;
			qx[tail]=nowx;qy[tail]=nowy;tail++;
			if(nowx==50&&nowy==50)return;
		}
	}
}
int main()
{
	freopen("horse.in","r",stdin);
	freopen("horse.out","w",stdout);
	xp=read();yp=read();xs=read();ys=read();
	x=abs(xp-xs);y=abs(yp-ys);
	
	while(x+y>=50)
	{
		if(x<y)swap(x,y);
		if(x-4>=2*y)x-=4;
		else x-=4,y-=2;	
		ans+=2;
	}
	
	x+=50;y+=50;
	bfs();
	printf("%d\n",ans+dis[50][50]);
	return 0;
}

