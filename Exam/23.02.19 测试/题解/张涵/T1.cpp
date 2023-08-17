#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<string>
#include<ctime>
#include<set>
#include<vector>
#include<map>
#include<cmath>
#include<queue>
#include<bitset>
#include<list>
#define File(x) freopen(""#x".in","r",stdin)
#define Look(x) freopen(""#x"","w",stdout)
#define rep(i,l,r) for(int i=l; i<r; ++i)
#define drep(i,r,l) for(int i=r; i>l; --i)
#define vi vector<int>
#define db double
#define debug cerr<<"ok"<<endl
#define CT cout<<TNT<<':'<<"--------------------------------"<<endl
using namespace std;
typedef long long LL;
int TNT;
template <class T>
inline void scan(T &a)
{
	a=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {a=(a<<1)+(a<<3)+ch-'0';ch=getchar();}
	a*=f;
}
void print(short date)
{
	if (date/10) print(date/10);
	putchar(date%10+48);  
}
priority_queue<int>q;
//#define int short 
int n,k;  
int ex[20];
struct PEO
{
	 int id;
	 int val;
}peo[100005];
bool cmp(PEO a,PEO b)
{
	if (a.val!=b.val) return a.val>b.val;
	return a.id<b.id;
}
signed main()
{
	scan(n);scan(k);
	for (int i=1;i<=10;i++) scan(ex[i]);
	for (int i=1;i<=n;i++) scan(peo[i].val),peo[i].id=i;
	//stable_sort(peo+1,peo+1+n,cmp);
	sort(peo+1,peo+1+n,cmp);
	for (int i=1;i<=n;i++)
	{
		peo[i].val+=ex[((i-1)%10)+1];	
	}
	sort(peo+1,peo+1+n,cmp);
	for (int i=1;i<=k;i++)
		printf("%d ",peo[i].id);
	return 0;
}

