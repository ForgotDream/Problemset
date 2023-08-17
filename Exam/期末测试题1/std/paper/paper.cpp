# include <cstdio>
# include <iostream>
# define fr(x) freopen(x,"r",stdin)
# define fw(x) freopen(x,"w",stdout)
using namespace std;
long long n,m,ans;
void calc(long long n,long long m)
{
    if(!m)return;
    ans+=n/m;
    calc(m,n%m);
}
int main()
{
    fr("paper.in");
	fw("paper.out");
	cin>>n>>m;
    calc(n,m);
    cout<<ans<<endl;
    return 0;
}
