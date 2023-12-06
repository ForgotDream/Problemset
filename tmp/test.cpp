typedef pair<int,int> pii;
typedef long long ll;
#define N 100010
#define M 1000100
int n,a[N],m,f[N][20],lg[N];
pii q[M];
vector<int> vec[M];
inline int Query(int l,int r){
	int k=lg[r-l+1];
	return min(f[l][k],f[r-(1<<k)+1][k]);
}
struct BIT{
	int b[N];
	inline int lowbit(int x){
		return x&(-x);
	}
	inline void Add(int x){
		while(x<=n){
			++b[x];
			x+=lowbit(x);
		}
	}
	inline int Ask(int x){
		int ans=0;
		while(x){
			ans+=b[x];
			x-=lowbit(x);
		}
		return ans;
	}
}B; 
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i){
		a[i]=m+1;
	}
	for(int i=1;i<=m;++i){
		int opt=read();
		q[i]={-1,-1};
		if(opt==1){
			int x=read();
			a[x]=min(a[x],i);
		}
		else{
			q[i].first=read(),q[i].second=read();
		}
	}
	for(int i=2;i<=n;++i){
		lg[i]=lg[i>>1]+1;
	}
	for(int i=1;i<=n;++i){
		f[i][0]=a[i];
	}
	for(int j=1;j<=18;++j){
		for(int i=1;i+(1<<j)-1<=n;++i){
			f[i][j]=min(f[i][j-1],f[i+(1<<j-1)][j-1]);
		}
	}
	for(int i=1;i<=n;++i){
		B.Add(i);
		int las=0;
		for(int j=1;j<=n;j+=i){
			vec[las=max(las,Query(j,min(j+i-1,n)))].push_back(i);
		}
	}
	for(int i=1;i<=m;++i){
		for(auto x:vec[i]){
			B.Add(x);
		}
		if(~q[i].first){
			printf("%d\n",B.Ask(q[i].second)-B.Ask(q[i].first-1));
		}
	}
	return 0;
}
