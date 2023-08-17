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
#define File(x) freopen(""#x".in","r",stdin)
#define Look(x) freopen(""#x"","w",stdout)
#define rep(i,l,r) for(int i=l; i<r; ++i)
#define drep(i,r,l) for(int i=r; i>l; --i)
#define vi vector<int>
#define db double
#define debug cerr<<"ok"<<endl
#define CT cout<<TNT<<':'<<"--------------------------------"<<endl
#include<unordered_map>
using namespace std;
#define int long long 
const int MOD=1000000007;
int pre[110000];
int n;
int date[110000];
int ans;
signed main()
{
	freopen("num.in","r",stdin);
	freopen("num.out","w",stdout);
	scanf("%lld",&n);
	pre[0]=1;
	for (int i=1;i<=n;i++)
	{
		pre[i]=pre[i-1]*2;
		pre[i]%=MOD;	
	}
	for (int i=1;i<=n+1;i++)
	{
		scanf("%lld",&date[i]);
	}
	for (int i=1,temp;i<=n;i++)
	{
		if (i==1) temp=pre[n];
		else temp=pre[n-1];
		for (int j=i+1;j<=n+1;j++)
		{
			ans+=(((date[i]*date[j])%MOD)*temp)%MOD;
			ans%=MOD;
			temp>>=1;
		}
	}
	printf("%lld",ans);
	return 0;
}
/*
				a b c d e f
			  b a c d e f
			  c a b d e f
			  d a b c e f 
			  e a b c d f
			  f a b c d e
			  
*/
/*
		a b c d e +++de
	  b a c d e   +++de
	  c a b d e   +++de
	  d a b c e   +++
	  e a b c d   +++
	c b a d e     +++de
	d b a c e     +++
	e b a c d     +++
	d c a b e     +++
	e c a b d     +++
	e d a b c     de+++
  d c b a e       +++
  e c b a d       +++
  e d b a c       de+++
  e d c a b       de+++
e d c b a         de+++

ab ac ad ae bc bd be cd ce de
16 8  4  2  8  4  2  8  4  8

16 ab
8 ac bc cd de
4 ad bd ce
2 ae be
a(16b+8c+4d+2e)
b(8c+4d+2e)
c(8d+4e)
d(8e)
*/
/*
		a b c d e ab+bc+cd+de
	  b a c d e   ab+ac+cd+de
	  c a b d e   ac+ab+bd+de
	  d a b c e   ad+ab+bc+ce
	  e a b c d   ae+ab+bc+cd
	c b a d e     bc+ab+ad+de
	d b a c e     bd+ab+ac+ce
	e b a c d     be+ab+ac+cd
	d c a b e     cd+ac+ab+be
	e c a b d     ce+ac+ab+bd
	e d a b c     de+ad+ab+bc
  d c b a e       cd+bc+ab+ae
  e c b a d       ce+bc+ab+ad
  e d b a c       de+bd+ab+ac
  e d c a b       de+cd+ac+ab
e d c b a         de+cd+bc+ab

*/
/*
		a b c d ++
	  d a b c   ++
	  c a b d   ++
	  b a c d   ++
	d c a b     ++
	c b a d     ++
	d b a c     ++
  d c b a       ++
	
  ab ac ad bc bd cd
  8  4  2  4  2  4
  
  a(8b+4c+2d)
  b(4c+2d)
  c(4d)
*/
/*
		a b c d ab+bc+cd
	  d a b c   ad+ab+bc
	  c a b d   ac+ab+bd
	  b a c d   ab+ac+cd
	d c a b     cd+ac+ab
	c b a d     bc+ab+ad
	d b a c     bd+ab+ac
  d c b a       cd+bc+ab
*/
/*
		a b c +
	  b a c   +
	  c a b   +
	c b a     +
	
	ab ac bc 
   	4  2  2
   	a(4b+2c)
   	b(2c)
*/
/*
		a b c ab+bc
	  b a c   ab+ac
	  c a b   ac+ab
	c b a     bc+ab
	ab ac bc 
	
*/
