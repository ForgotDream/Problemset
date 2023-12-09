#include<algorithm>
#include<cstdio>
#define ll long long
#define mod 1000000007
#define Maxn 305
using namespace std;
ll powM(ll a,int t=mod-2)
{
  ll ans=1;
  while(t){
    if (t&1)ans=ans*a%mod;
    a=a*a%mod;t>>=1;
  }return ans;
}
int n,m;
ll *a[Maxn],_a[Maxn][Maxn];
ll det(ll **a)
{
  ll ans=1;bool tr=0;
  for (int j=1;j<n;j++){
    for (int i=j;i<n;i++)
      if (a[i][j]){
        if (i!=j){
          swap(a[i],a[j]);
          tr=!tr;
        }break;
      }
    if (a[j][j]==0)return 0;
    ans=ans*a[j][j]%mod;
    ll t=powM(a[j][j]);
    for (int k=j;k<n;k++)a[j][k]=t*a[j][k]%mod;
    for (int i=j+1;i<n;i++){
      t=mod-a[i][j];
      for (int k=j;k<n;k++)
        a[i][k]=(a[i][k]+t*a[j][k])%mod;
    }
  }return tr? (mod-ans)%mod : ans;
}
int op;
int main()
{
  scanf("%d%d%d",&n,&m,&op);
  for (int i=1;i<=n;i++)a[i]=_a[i];
  for (int i=1,f,t,w;i<=m;i++){
    scanf("%d%d%d",&f,&t,&w);
    if (f==n)f=1;else if (f==1)f=n;
    if (t==n)t=1;else if (t==1)t=n;
    if (op==1){
      a[f][t]=(a[f][t]-w+mod)%mod;
      a[t][t]=(a[t][t]+w)%mod;
    }else {
      a[f][t]=(a[f][t]-w+mod)%mod;
      a[t][t]=(a[t][t]+w)%mod;
      a[t][f]=(a[t][f]-w+mod)%mod;
      a[f][f]=(a[f][f]+w)%mod;
    }
  }printf("%lld",det(a));
  return 0;
}
