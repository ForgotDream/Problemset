#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<set>
#include<string>
#include<queue>
#include<stack>
#include<ctime>
using namespace std;
#define ldouble long double
#define eps 1e-6
int Next[1100][1100];
inline void getNext(string Word,int len,int Next[])
{
	int i=0,j=-1;
	Next[0]=-1;
	while (i<=len)
	{
		if(j==-1||Word[i]==Word[j])
			Next[++i]=++j;
		else j=Next[j];
	}
}
inline int KMP(string M,int lenm,string T,int lent,int Next[])
{
	int i=0,j=0,res=0;
	while (i<lenm)
	{
		if(j==-1||M[i]==T[j])
		{
			i++,j++;
			if (j==lent) 
			{
				res++;
				j=Next[j];
				continue;
			}
		}
		else j=Next[j];
	}
	return res;
}
string Word[1010];
int n,L;
int A[1010];
inline int GetDis(string a,string b)
{
	int i=a.length()-1,j=0,res=0;
	while (0<i&&j<b.length()-1)
	{
		if (a.substr(i)==b.substr(0,j+1))
			res=j+1;
		i--,j++;
	}
	return res;
}
inline string Merge(string a,string b)
{
	return a+b.substr(GetDis(a,b));
}
string AAA;
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>L;
	for (int i=1;i<=n;i++)
		cin>>A[i];
	for (int i=1;i<=n;i++)
		cin>>Word[i];
	if (n==1)
	{
		AAA=Word[1];
		while (AAA.length()<=L)
			AAA=Merge(AAA,Word[1]);
		getNext(Word[1],Word[1].length(),Next[1]);
		printf("%d\n",A[1]*KMP(AAA,L,Word[1],Word[1].length(),Next[1]));
		return 0;
	}
	else
	{
		int ans=0;
		for (int i=1;i<=n;i++)
			getNext(Word[i],Word[i].length(),Next[i]); 
		AAA="";
		for (int i=1;i<=L;i++) AAA+='b';
		for (int i=0,res;i<=(1<<L)-1;i++)
		{
			res=0;
			for (int j=1;j<=L;j++)
			{
				if ((i>>(j-1))&1)
				{
					AAA[j-1]='a';
				}
				else AAA[j-1]='b';
			}
			for (int j=1;j<=n;j++)
			{
				res+=A[j]*KMP(AAA,L,Word[j],Word[j].length(),Next[j]);
			}
			ans=max(ans,res);
		}
		printf("%d",ans);
		return 0;
	}
	return 0;
}
