# include <cstdio>
# define N 1000000
const long long INF=1e18; 
using namespace std;
long long sum[N+1]; 
int main()
{   
    freopen("select.in","r",stdin);
	freopen("select.out","w",stdout); 
	int n;
    long long ans=-INF;
	long long min_s=0;
    scanf("%d",&n);
    for(int i=1; i<=n; ++i)
    {
        int a;
		scanf("%d",&a);
        sum[i]=sum[i-1]+a;
    }
    for(int i=1; i<=n; ++i)
    {
        if(sum[i]-min_s>ans) ans=sum[i]-min_s;
		if(sum[i]<min_s) min_s=sum[i];    
    }
    printf("%lld\n",ans);
    return 0;
}
