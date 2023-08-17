#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<unordered_map>
#include<set>
#include<bitset>
using namespace std;
/*struct TRIE
{
	int tree[1000005][2];
	int tot;
	int isEnd[1000005];
	inline void insert(int date[])
	{
		
	}
}*/
int n;
struct Magic
{
	bitset<1005>date;
	int sumzero;
	int sumXor;
	bool operator <(const Magic &b)const
	{
		if (sumXor!=b.sumXor) return sumXor<b.sumXor;
		return sumzero>b.sumzero;
	}
}magic[1005];
bitset<1005>temp;
char Read[1005];
int sumone[1005];
int sumzero[1005];
int L;
int main()
{
	freopen("curse.in","r",stdin);
	freopen("curse.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%s",Read);
		L=strlen(Read);
		//cerr<<L<<endl;
		for (int j=0;j<L;j++)
			magic[i].date[j+1]=Read[j]-'0',magic[i].sumzero+=Read[j]-'0';
		magic[i].sumzero=L-magic[i].sumzero;
	}
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
		{
			temp=magic[i].date^magic[j].date;
			for (int k=1;k<=L;k++)
				if (temp[k])
					magic[i].sumXor++,magic[j].sumXor++;
		}
	sort(magic+1,magic+1+n);
	for (int i=1;i<=L;i++)
		putchar(magic[1].date[i]+'0');
	return 0;
}
/*
freopen("curse.in","r",stdin);
	freopen("curse.out","w",stdout);
*/
