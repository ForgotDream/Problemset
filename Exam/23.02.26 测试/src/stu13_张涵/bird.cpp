#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<string>
#include<cmath>
#include<unordered_map>
#include<set>
#include<bitset>
#include<queue>
using namespace std;
int n,q;
int x,y;
struct SPACE
{
	int x,y,x2,y2;
}bird;
inline int qdis(SPACE a)
{
	if ((a.x<=x&&x<=a.x2)&&(a.y<=y&&y<=a.y2))//点在矩形内 
		return 0;
	if (a.y<=y&&y<=a.y2)
	{
		return min(abs(x-a.x),abs(x-a.x2));
	}
	if (a.x<=x&&x<=a.x2)
	{
		return min(abs(y-a.y),abs(y-a.y2));
	}
	int temp1,temp2;
	temp1=min(abs(x-a.x)+abs(y-a.y),abs(x-a.x)+abs(y-a.y2));
	temp2=min(abs(x-a.x2)+abs(y-a.y),abs(x-a.x2)+abs(y-a.y2));
	return min(temp1,temp2);
}
inline int qdis2(SPACE a)
{
	int temp1,temp2;
	temp1=max(abs(x-a.x)+abs(y-a.y),abs(x-a.x)+abs(y-a.y2));
	temp2=max(abs(x-a.x2)+abs(y-a.y),abs(x-a.x2)+abs(y-a.y2));
	return max(temp1,temp2);
}
struct POINT
{
	int maxdis;
	int mindis;
};
int tree[8000005];
int tag[8000005];
void add(int k,int l,int r,int val)
{
	tree[k]+=(l-r+1)*val;
	tag[k]+=val;
}
void pushdown(int k,int l,int r,int mid)
{
	if (tag[k]==0) return ;
	add(k<<1,l,mid,tag[k]);
	add(k<<1|1,mid+1,r,tag[k]);
	tag[k]=0;
}
void change(int k,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)
	{
		tree[k]+=l-r+1;
		tag[k]++;
		return ;
	}
	int mid=(l+r)>>1;
	if (x<=mid) change(k<<1,l,mid,x,y);
	if (mid+1<=y) change(k<<1|1,mid+1,r,x,y);
	tree[k]=tree[k<<1]+tree[k<<1|1];
}
int query(int k,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)
	{
		return tree[k];
	}
	int mid=(l+r)>>1,res=0;
	pushdown(k,l,r,mid);
	if (x<=mid) res+=query(k<<1,l,mid,x,y);
	if (mid+1<=y) res+=query(k<<1|1,mid+1,r,x,y);
	return res;
}
int main()
{
	freopen("bird.in","r",stdin);
	freopen("bird.out","w",stdout);
	scanf("%d %d %d %d",&n,&q,&x,&y);
	for (int i=1;i<=n;i++)
	{
		scanf("%d %d %d %d",&bird.x,&bird.y,&bird.x2,&bird.y2);
		if (bird.x>bird.x2) swap(bird.x,bird.x2);
		if (bird.y>bird.y2) swap(bird.y,bird.y2);
		change(1,1,2000000,qdis(bird)+1,qdis2(bird)+1);
	}
	int k;
	while(q--)
	{
		scanf("%d",&k);
		k++;
		printf("%d\n",query(1,1,2000000,k,k));
	}
	return 0;
}
/*
二维平面上有一大堆矩形
现在有一个中心为定点的正方形 
请问这个正方形与多少个矩形有交集
能拿K/D 写，但是我不会就很淦 

我们考虑求出每个矩形到正方形中心的曼哈顿距离
求出最短和最大距离 
*/
