#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<unordered_map>
#include<set>
#include<bitset>
using namespace std;
int N,R,G;
int magic[2100];
int canR[2100];
int canG[2100];
bool dfs(int pos,int L,int restR,int restG)
{
	if (pos==N+1) return true;
	if (restR+restG>=N-pos+1) return true;
	if (restR==0&&restG==0) return false;
	if (canG[pos]<=restG) return true;
	if (canR[pos]<=restR) return true;
	int Next,NNext;
	Next=NNext=pos;
	if (restR&&restG)
	{
		while (magic[Next]-magic[pos]+1<=L&&Next<=N) Next++;
		Next=min(Next,N);
		if (magic[Next]-magic[pos]+1>L) Next--;	
		if (dfs(Next+1,L,restR-1,restG)) return true;
		
		while (magic[NNext]-magic[pos]+1<=L*2&&NNext<=N) NNext++;
		NNext=min(NNext,N);
		if (magic[NNext]-magic[pos]+1>L*2) NNext--;
		if (dfs(NNext+1,L,restR,restG-1)) return true;
		
		return false;
	}
	if (restG)
	{
		if (canG[pos]<=restG) return true;
		return false;
	}
	if (restR)
	{
		if (canR[pos]<=restR) return true;
		return false;
	}
	return false;
}
inline bool check(int mid)
{
	int last=N;
	canR[N]=canG[N]=1;
	for (int i=N-1;i>=1;i--)
	{
		if (magic[last]-magic[i]+1<=mid) canR[i]=canR[i+1];
		else canR[i]=canR[i+1]+1,last=i;
		if (canR[i]>R) canR[i]=1e9;
	}
	last=N;
	for (int i=N-1;i>=1;i--)
	{
		if (magic[last]-magic[i]+1<=mid*2) canG[i]=canG[i+1];
		else canG[i]=canG[i+1]+1,last=i;
		if(canG[i]>R) canG[i]=1e9;
	}
	return dfs(1,mid,R,G);
}
int L;
int l,r,mid; 
int main()
{
	freopen("light.in","r",stdin);
	freopen("light.out","w",stdout);
	scanf("%d %d %d",&N,&R,&G);
	for (int i=1;i<=N;i++)
		scanf("%d",&magic[i]);
	if (R+G>=N)
	{
		printf("1");
		return 0;
	}
	sort(magic+1,magic+1+N);
	l=1;r=1e9/(R+G);
	while (l<r)
	{
		mid=(l+r)/2;
		if (check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%d",l);
	return 0;
}
