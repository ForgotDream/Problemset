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
/*struct Magic
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
bitset<1005>temp;*/
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
		for (int j=0;j<L;j++)
			if (Read[j]=='0') sumzero[j+1]++;
			else sumone[j+1]++;
	}
	for (int i=1;i<=L;i++)
	{
		if (sumone[i]>sumzero[i]) putchar('1');
		else putchar('0');
	}
	return 0;
}
/*
freopen("curse.in","r",stdin);
	freopen("curse.out","w",stdout);
*/
