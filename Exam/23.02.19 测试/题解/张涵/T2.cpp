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
//#define int short 
int n,k;  
int price[1100],P[1100];
struct Med
{
	int a,b;
	int get;
	int delta;
}med[100000];
bool CMP(Med a,Med b)
{
	return a.delta>b.delta;
}
int cnt;
int minans,ans;
//int have[1100];
vector<int>temp[1100];
int dfs(int pos)
{
	//cout<<"pos"<<pos<<endl;
	int res=0;
	if (price[pos]==P[pos]) res++;
	bool flag=true;
	for (int i=0,to1,to2,temp1,temp2;i<temp[pos].size();i++)
	{
		to1=med[temp[pos][i]].a;
		to2=med[temp[pos][i]].b;
		if (price[to1]+price[to2]>price[pos]) continue;
		flag=false;
		temp1=dfs(to1);
		temp2=dfs(to2);
		res+=temp1*temp2;
		//cout<<to1<<' '<<to2<<' ';
		//cout<<temp1<<' '<<temp2<<' ';
		//cout<<res<<endl;
	}
	if (flag) res=1;
	return res;
}
signed main()
{
	cin>>n; 
	for (int i=0;i<n;i++) cin>>price[i],P[i]=price[i];;
	int x,y,z;
	while (cin>>x>>y>>z)
	{
		med[++cnt].a=x;
		med[cnt].b=y;
		med[cnt].get=z;
		med[cnt].delta=price[z]-(price[x]+price[y]);
		temp[z].push_back(cnt);
	}
	minans=price[0];
	bool flag=true; 
	while (1)
	{
		flag=true;
		for (int i=1;i<=cnt;i++)
		{
			if (med[i].delta>0)
			{
				flag=false;
				price[med[i].get]-=med[i].delta;
				for (int j=i+1;j<=cnt;j++)
				{
					med[j].delta=price[med[j].get]-price[med[j].a]-price[med[j].b];
				}
			}
		}
		for (int j=1;j<=cnt;j++)
		{
			med[j].delta=price[med[j].get]-price[med[j].a]-price[med[j].b];
		}
		if (minans>price[0]) minans=price[0];
		if (flag) break;
	}
	ans+=dfs(0);
	cout<<price[0]<<' '<<ans;
	return 0;
}
/*
a+b->c
��� p[a]+p[b]>p[c]
���Ե�Ч��Ϊ��һ����c����ѡ�� 
��������� ��ֱ�Ӹ� c ��ֵ��Ȼ��ɵ����ҩ�� 
*/