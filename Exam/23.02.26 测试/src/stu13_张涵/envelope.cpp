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
#define int long long 
using namespace std;
int n,k;
struct CARD
{
	int l,h,num;
}card[20];
bool CMP(CARD a,CARD b)
{
	if (a.l!=b.l) return a.l<b.l;
	return a.h<b.h;
}
int belong[20];
int ans=0x7f7f7f7f;
int prel[20],prer[20];
int l[20],r[20],cnt;
unordered_map<int ,int >book;
void dfs(int sumeve,int step,int sum)
{
	if (sumeve>k) return ;
	if (step==n+1)
	{
		ans=min(ans,sum);
		return ;
	}
	if (sum>=ans) return ;
	bool flag=false;
	int temp=0x7f7f7f7f;
	for (int j=1;j<=cnt;j++)
		if (l[j]>=card[step].l&&r[j]>=card[step].h)
			temp=min(temp,l[j]*r[j]-card[step].h*card[step].l);
	if (sumeve==k)
	{
		if (temp!=0x7f7f7f7f) dfs(sumeve,step+1,sum+temp*card[step].num);
		return ;
	}
	if (temp!=0x7f7f7f7f)dfs(sumeve,step+1,sum+temp*card[step].num);
	int ll,rr;
	for (ll=1;ll<=n;ll++) if (prel[ll]==card[step].l) break;
	for (rr=1;rr<=n;rr++) if (prer[rr]==card[step].h) break;
	int temp2;
	for (int i=ll;i<=n;i++)
	{
		for (int j=rr;j<=n;j++)
		{
			if (book[i*100+j]) continue;
			else book[i*100+j]=1;
			cnt++;
			l[cnt]=prel[i];r[cnt]=prer[j];
			temp2=(prel[i]*prer[j]-card[step].h*card[step].l);
			if (temp2<temp) dfs(sumeve+1,step+1,sum+temp2*card[step].num);
			cnt--;
			book[i*100+j]=0;
		}
	}
}
signed main()
{
	freopen("envelope.in","r",stdin);
	freopen("envelope.out","w",stdout);
	cin>>n>>k;
	if (k==n)
	{
		cout<<"0"<<endl;
		return 0;
	}
	int ml=0,mh=0;
	for (int i=1;i<=n;i++)
	{
		cin>>card[i].l>>card[i].h>>card[i].num;
		ml=max(ml,card[i].l);
		mh=max(mh,card[i].h);
		prel[i]=card[i].l;prer[i]=card[i].h;
	}
	sort(prel+1,prel+1+n);sort(prer+1,prer+1+n);
	if (k==1)
	{
		ans=0;
		for (int i=1;i<=n;i++)
		{
			ans+=((ml*mh)-card[i].l*card[i].h)*card[i].num;
		}
		cout<<ans;
		return 0;
	}
	dfs(0,1,0);
	cout<<ans;
	return 0;
}
