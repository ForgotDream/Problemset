# include <cstdio>
# include <algorithm>
# include <cstring>
using namespace std;
typedef long long LL;
int T;
LL N,h;
int A[21],cnt;
LL F[21][21][2];
LL dfs(int cur,int pre,bool less,bool last)
{
    if(cur>cnt) return 1ll;
    if(less&&F[pre][cur][last?1:0]!=-1) return F[pre][cur][last?1:0];
    int lim=less?9:A[cur];
    LL re=0;
    for(int i=0;i<=lim;i++)
    {
        if(i==4) continue;
        else if(i==3&&last) continue;
        else if(i==0&&cur==pre)
            re+=dfs(cur+1,pre+1,true,false);
        else if(i==1)
            re+=dfs(cur+1,pre,less||i<A[cur],true);
        else
            re+=dfs(cur+1,pre,less||i<A[cur],false);
    }
    if(less) F[pre][cur][last?1:0]=re;
    return re;
}
int main()
{
    //freopen("1.in","r",stdin);
    freopen("height.in","r",stdin);
    freopen("height.out","w",stdout);
    scanf("%d",&T);
    while(T--)
    {
        cnt=0;
        memset(F,-1,sizeof(F));
        scanf("%lld%lld",&N,&h);
        while(N)
        {
            A[++cnt]=N%10;
            N/=10;
        }
        for(int i=1;i<=cnt/2;i++)
            swap(A[i],A[cnt-i+1]);
        printf("%lld\n",(dfs(1,1,false,false)-1)*h);
    }
    return 0;
}
