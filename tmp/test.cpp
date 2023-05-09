#include<cstdio>
#include <cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include <stack>
#include<deque>
#include<map>
#include <utility>
#include<cmath>
#include <vector>
using namespace std;
typedef long long ll;
typedef long double ldouble;
typedef unsigned long long ull;
int n,m,tot;
int ST[4005][20];
int main()
{
    cin>>n;
    for (int i=1;i<=n;i++)
        for (int j=0;i+(1<<j)-1<=n;j++)
            ST[i][j]=++tot;
    cout<<tot<<endl;
    for (int i=1;i<=n;i++)
        for (int j=0;i+(1<<j)-1<=n;j++)
            cout<<i<<' '<<i+(1<<j)-1<<endl;
    int q,x,y,k;
    cin>>q;
    while (q--)
    {
        cin>>x>>y;
        k=log2(y-x+1);
        cout<<ST[x][k]<<' '<<ST[y-(1<<k)+1][k]<<endl;
    }
    return 0;
}