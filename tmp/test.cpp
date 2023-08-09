#include<bits/stdc++.h>
using namespace std;
mt19937 rd(time(0));
struct T{
	int l,r,d,mn,mx,s,h;
}s[100009];
int n,k,h,r;
void up(int x){//更新size，最大值，最小值
	s[x].mn=min(s[x].h,min(s[s[x].l].mn,s[s[x].r].mn));
	s[x].mx=max(s[x].h,max(s[s[x].l].mx,s[s[x].r].mx));
	s[x].s=s[s[x].l].s+s[s[x].r].s+1;
}
void sp(int x,int k,int&p,int&q){//分裂
	if(!x){p=q=0;return;}
	if(s[s[x].l].s<k)p=x,sp(s[x].r,k-s[s[x].l].s-1,s[x].r,q);else q=x,sp(s[x].l,k,p,s[x].l);
	up(x);
}
int mg(int x,int y){//合并
	if(!x||!y)return x|y;
	if(s[x].d<s[y].d)return s[x].r=mg(s[x].r,y),up(x),x;
	return s[y].l=mg(x,s[y].l),up(y),y;
}
int e1(int x){//求最小的w满足x子树内第w+1~sizex个元素属于[h-k,h+k]
	int w=0;
	while(x)if(min(s[x].h,s[s[x].r].mn)<h-k||max(s[x].h,s[s[x].r].mx)>h+k)w+=s[s[x].l].s+1,x=s[x].r;else x=s[x].l;
	return w;
}
int e2(int x){//求最小的w满足x子树内第w+1个元素大于h
	int w=0;
	while(x)if(max(s[s[x].l].mx,s[x].h)>h)x=s[x].l;else w+=s[s[x].l].s+1,x=s[x].r;
	return w;
}
void dfs(int x){if(x)dfs(s[x].l),cout<<s[x].h<<'\n',dfs(s[x].r);}//中序遍历
int main(){ios::sync_with_stdio(0),cin.tie(0);
	int i,x,y;
	for(cin>>n>>k,s[0].mn=2e9,s[0].mx=0,i=1;i<=n;++i){
		cin>>h,s[i]={0,0,(int)rd(),h,h,1,h};
		int t1, t2;
		sp(r,t1 = e1(r),x,r),sp(r,t2 = e2(r),y,r),r=mg(mg(x,y),mg(i,r));
		std::cerr << t1 << " " << t2 << "\n";
	}
	dfs(r);
}
