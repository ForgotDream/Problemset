# include <cstdio>
# include <algorithm>
# define reg register

int G[25][25],c[25],n,tot_degree,ans = 1;

inline bool comp(const int a,const int b){return a > b;}

int main()
{
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    
	scanf("%d",&n);
	
	for(reg int i = 1; i <= n ; ++i) scanf("%d",c+i);
	
	for(reg int i = 1; i <= n ; ++i) tot_degree += c[i];
	
	if(tot_degree == (n-1)<<1)
	{
		//dfs(1,tot_degree,1,1,n);
		
		for(reg int i = 1; i <= n ; ++i) 
			if(c[i] >= 2) ++ans;
			else if(c[i] <= 0) return puts("-1"),0;
		
		printf("%d",ans);
	}
	else puts("-1");
	
	return 0;
} 
