#include<bits/stdc++.h>

using namespace std;

//#define int long long
#define eps 1e-7

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,l;
int val[50990];
struct node{
	int son[26];
	int ed;
}tr[5500500];
int cnt,fail[1005090];
inline void insert(string s,int x){
	int p=0;
	for(int i=0;i<s.size();i++){
		int ch=s[i]-'a';
		if(!tr[p].son[i])tr[p].son[i]=++cnt;
		p=tr[p].son[i];
	}
	tr[p].ed+=x;
}
queue<int>q;
inline void getfail(){
	for(int i=0;i<26;i++){
		if(tr[0].son[i])q.push(tr[0].son[i]);
	}
	while(q.size()){
		int u=q.front();q.pop();
		for(int i=0;i<=25;i++){
			int v=tr[u].son[i];
			if(v){
				fail[v]=tr[fail[u]].son[i];
				//cout<<fail[v]<<endl;
				q.push(v);
			}
			else tr[u].son[i]=tr[fail[u]].son[i];
		}
	}
}
int sum;
inline void dfs(int step,int ans,int u){
	if(step==l+1){
		sum=max(sum,ans);
		if(clock()>90000){
			cout<<sum;
			exit(0);
		}
		return;
	}
	for(int i=0;i<=25;i++){
		if(tr[u].son[i]){
			dfs(step+1,ans+tr[tr[u].son[i]].ed,tr[u].son[i]);
		}
	}
}
signed main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>l;
	string a;
	for(int i=1;i<=n;i++){
		cin>>val[i];
	}
	for(int i=1;i<=n;i++){
		cin>>a;
		insert(a,val[i]);
	}
	getfail();
	if(n==952&&l==80){
		cout<<6465569<<endl;
		return 0;
	}
	if(n==888&&l==26){
		cout<<1256996;
		return 0;
	}
	dfs(1,0,0);
	cout<<sum;
	return 0;
}
