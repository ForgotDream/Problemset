#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<set>
#include<iostream>
#include<unordered_map>
#define int long long 
using namespace std;
struct Node
{
	int l,r;
	mutable int val;
	Node()
	{
		l=r=val=0;
	}
	bool operator < (const Node &b)const
	{
		return l<b.l;
	}
	Node(int L,int R,int V)
	{
		l=L;r=R;val=V;
	}
};
set<Node>s;
inline void debug()
{
	putchar('\n');
	for (set<Node>::iterator it=s.begin();it!=s.end();it++)
		printf("%lld %lld %lld\n",it->l,it->r,it->val);
	putchar('\n');
}
inline set<Node>::iterator split(int pos)
{
	set<Node>::iterator it=s.lower_bound(Node(pos,0,0));
	if (it!=s.end()&&it->l==pos) return it;
	it--;
	//if (it->r<pos) return s.end();
	int l=it->l,r=it->r,w=it->val;
	/*cerr<<"here\n";
	cerr<<pos<<endl;
	cerr<<l<<' '<<r<<' '<<w<<endl<<endl;*/
	//debug();
	s.erase(it);
	//debug();
	s.insert(Node(l,pos-1,w));
	//debug();
	return s.insert(Node(pos,r,w)).first;
}
inline void assign(int l,int r,int x)
{
	set<Node>::iterator itr=split(r+1),itl=split(l);
	//debug();
	//cout<<itl->l<<' '<<itl->r<<' '<<itl->val<<'\n';
	//cout<<itr->l<<' '<<itr->r<<' '<<itr->val<<'\n';
	s.erase(itl,itr);
	//debug();
	s.insert(Node(l,r,x));
	//debug();
}
inline int qsum(int l,int r)
{
	int res=0;
	set<Node>::iterator itr=split(r+1),itl=split(l);
	for (set<Node>::iterator it=itl;it!=itr;it++)
		res+=it->val*(it->r-it->l+1);
	return res;
}
int st,n;
int a,b,t;
signed main()
{
	freopen("china.in","r",stdin);
	freopen("china.out","w",stdout);
	scanf("%lld %lld",&st,&n);
	s.insert(Node(-100,st+100,1));
	assign(1,st,1);
	while (n--)
	{
		scanf("%lld %lld %lld",&a,&b,&t);
		assign(a,b,t);
	}
	printf("%lld",qsum(1,st));
	return 0;
}
