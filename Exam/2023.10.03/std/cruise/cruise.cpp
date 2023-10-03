#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 +5;
struct edge{
    double v,s,len;
}es[maxn];
int main()
{
    freopen("cruise.in","r",stdin);
    freopen("cruise.out","w",stdout);
    int n,test;
    scanf("%d",&test);
    while(test--)
    {
        int m = 1;
        scanf("%d", &n);
        for(int i = 1;i <= n + 1;i++) scanf("%lf",&es[i].len);
        for(int i = 1;i <= n + 1;i++) scanf("%lf",&es[i].s);
        for(int i = 1;i <= n + 1;i++) scanf("%lf",&es[i].v);
        double ans = 0;
        double lazy = 0;
        for(int i = 1;i <= n + 1;i++)
        {
            if(i != 1) lazy += es[i].len;
            double t = (es[i].s + lazy) / es[i].v;
            ans = max(t,ans);
        }
        printf("%.10f\n",ans);
    }
    return 0;
}