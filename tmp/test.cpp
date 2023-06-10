#include <iostream>
#define ll long long
using namespace std;
const int N=101;
const ll mod=998244353;
ll n;
int m,cnt=100;
struct node
{
    ll a[N][N];
    node operator=(node rhs) {
        for (int i = 1; i <= cnt; i++) {
            for (int j = 1; j <= cnt; j++) {
                a[i][j] = rhs.a[i][j];
            }
        }
        return *this;
    }
}res,c;
node mul(node x,node y)
{
    for(int i=1;i<=cnt;++i)
    {
        for(int j=1;j<=cnt;++j)
        {
            for(int k=1;k<=cnt;++k)
            {
                c.a[i][j]+=x.a[i][k]*y.a[k][j]%mod;
                c.a[i][j]%=mod;
            }
        }
    }
    return c;
}
int main()
{
    scanf("%lld%d",&n,&m);
    res=mul(res,res);//此处去掉将不会异常退出 
    std::cout << "OK\n";
    return 0;
}