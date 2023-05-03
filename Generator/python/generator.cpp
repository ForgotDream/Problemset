#include<bits/stdc++.h>
#define up(l, r, i) for(i64 i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(i64 i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64; const i64 MAXN= 2e6 + 3;
vector <i64> V[MAXN], P[MAXN];
i64 n, m, W[MAXN], F[MAXN];
bool S[MAXN];
void dfs(i64 u, i64 f){
    for(auto &v : V[u]) if(v != f){
    F[v] = u; if(S[v] == 0) P[u].push_back(v);
    dfs(v, u);
}
}
using pii = pair<i64, i64>;
priority_queue <pii > Q;
void add(i64 x){ S[x] = 1, Q.push({W[x], x}); }
void del(i64 x){ S[x] = 0; }
i64 get(){
    while(S[Q.top().second] == 0) Q.pop();
    return Q.top().first;
}
signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    //n = qread(), m = qread();
    cin>>n>>m;
    W[0] = -1, add(0);
    up(1, n - 1, i){
        //i64 u = qread(), v = qread();
        i64 u,v;
        cin>>u>>v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    up(1, n, i) 
        //W[i] = qread();
        cin>>W[i];
    up(1, n, i) 
    {
        //S[i] = qread();
        cin>>S[i];
        S[i] ? add(i) : void();
    }
    dfs(1, 0);
    //printf("%d\n", get());
    cout<<get()<<'\n';
    up(1, m, i){
        //i64 x = qread();
        i64 x;
        cin>>x;
        if(S[x] == 0) S[x] = 1, add(x); else {
        del(x), P[F[x]].push_back(x);
        for(auto &s : P[x]) if(S[s] == 0) add(s);
        P[x].clear();
    }
    //printf("%d\n", get());
    cout<<get()<<'\n';
    }
    return 0;
}