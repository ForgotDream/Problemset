#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
using namespace std;
typedef long long LL;
const int maxn=100007;
const LL mod=1e9+7;
LL TREE[maxn<<2],mul[maxn<<2];
LL fast_pow(LL b,LL k)
{
    LL s=1;
    while(k)
    {
        if(k&1) s=s*b%mod;
        b=b*b%mod;
        k>>=1;
    }
    return s;
}
LL inv,p2;
LL A[maxn];
LL N;
#define mid ((L+R)>>1)
#define Ls (i<<1)
#define Rs (i<<1|1)
#define val(i) TREE[i]
void Build(int L,int R,int i)
{
    mul[i]=1;
    if(L==R)
    {
        val(i)=p2*A[L]%mod;
        return ;
    }
    Build(L,mid,Ls);
    Build(mid+1,R,Rs);
    val(i)=(val(Ls)+val(Rs))%mod;
    return ;
}
inline void pushdown(int i)
{
    if(mul[i]==1) return ;
    mul[Ls]=mul[Ls]*mul[i]%mod;
    mul[Rs]=mul[Rs]*mul[i]%mod;
    val(Ls)=val(Ls)*mul[i]%mod;
    val(Rs)=val(Rs)*mul[i]%mod;
    mul[i]=1;
    return ;
}
void Update(int L,int R,int l,int r,LL k,int i)
{
    if(l<=L&&R<=r)
    {
        mul[i]=(mul[i]*k)%mod;
        val(i)=(val(i)*k)%mod;
        return ;
    }
    pushdown(i);
    if(l<=mid) Update(L,mid,l,r,k,Ls);
    if(r>mid) Update(mid+1,R,l,r,k,Rs);
    val(i)=(val(Ls)+val(Rs))%mod;
    return ;
}
LL Query(int L,int R,int l,int r,int i)
{
    if(l<=L&&R<=r) return val(i);
    pushdown(i);
    LL re=0;
    if(l<=mid) re+=Query(L,mid,l,r,Ls);
    if(r>mid) re+=Query(mid+1,R,l,r,Rs);
    return re%mod;
}
int main()
{
    //freopen("1.in","r",stdin);
    freopen("num.in","r",stdin);
    freopen("num.out","w",stdout);
    scanf("%d",&N);p2=fast_pow(2,N);
    inv=fast_pow(2,mod-2);
    for(int i=1;i<=N+1;i++)
        scanf("%lld",&A[i]);
    Build(1,N,1);
    LL ans=0;
    for(int i=2;i<=N+1;i++)
    {
        ans+=A[i]*Query(1,N,1,i-1,1);
        ans%=mod;
        Update(1,N,1,i,inv,1);
    }
    printf("%lld",ans);
    return 0;
}
