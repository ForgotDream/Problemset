# include <cstdio>
# include <algorithm>
using namespace std;
const int N=100005;
int L[N],R[N],eat[N],ans=0;
int main()
{
   freopen("food.in","r",stdin);
   freopen("food.out","w",stdout);   
   int n,m,cnt;
   scanf("%d",&n);for(int i=1; i<=n; i++) scanf("%d",&R[i]);
   cnt=1;eat[cnt]=R[1];//初始化 
   for(int i=2; i<=n; i++)
   {
   		int pos=upper_bound(eat+1,eat+cnt+1,R[i])-eat;//等于的要吃 
		eat[pos]=R[i];//eat数组存在相同的好吃度
		cnt=max(cnt,pos); 
   } 
   ans+=cnt;
   scanf("%d",&m);for(int i=1; i<=m; i++) scanf("%d",&L[i]);
   cnt=1;eat[cnt]=L[1];//初始化 
   for(int i=2; i<=m; i++)
   {
   		int pos=lower_bound(eat+1,eat+cnt+1,L[i])-eat;//等于的不吃 
		eat[pos]=L[i];//eat数组不存在相同的好吃度 
		cnt=max(cnt,pos);  
   } 
   ans+=cnt;
   printf("%d",ans);
   return 0;   
}
