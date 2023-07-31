#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,s,a,b,cnt=0,deep[500009],fa[500009],son[500009],tot=0,id[500009],ltop[500009],c;
ll w[500009],w2[500009],ans[500009],lazy[500009],kkk,siz[500009],maxn[500009],q;
string k;
struct node 
{
    ll to,next;
} e[5000009];
ll head[5000009];
void add(ll x,ll y) 
{
    e[++cnt].to=y,e[cnt].next=head[x],head[x]=cnt;
}
//----------------------------------------------------------------------------
inline void push_down(ll rt,ll lenn) 
{
    lazy[rt<<1]+=lazy[rt];
    lazy[rt<<1|1]+=lazy[rt];
    ans[rt<<1]+=lazy[rt]*(lenn-(lenn>>1));
    ans[rt<<1|1]+=lazy[rt]*(lenn>>1);
    lazy[rt]=0;
}
void build(ll x,ll l,ll r) {
    if(l==r) 
    {
        ans[x]=w2[id[l]];
        maxn[x]=w2[id[l]];
        return ;
    }
    ll mid=(l+r)/2;
    build(x*2,l,mid);
    build(x*2+1,mid+1,r);
    ans[x]=(ans[x*2]+ans[x*2+1]);
    maxn[x]=max(maxn[x*2],maxn[x*2+1]);
}
void getsum(ll x,ll l,ll r,ll L,ll R) 
{
    if(L<=l&&R>=r) 
    {
        kkk+=ans[x];
        return ;
    } 
    else 
    {
        ll mid=(l+r)/2;
        push_down(x,r-l+1);
        if(L<=mid) 
        {
            getsum(x*2,l,mid,L,R);
        }
        if(R>mid)
        {
            getsum(x*2+1,mid+1,r,L,R);
        }
    }
}
ll getmax(ll x,ll l,ll r,ll L,ll R)
{
    if(L<=l&&R>=r) 
    {
        return maxn[x];
    } 
    else 
    {
        ll maxnn=-1,mid=(l+r)/2;
        if(L<=mid) 
        {
            maxnn=max(maxnn,getmax(x*2,l,mid,L,R));
        }
        if(R>mid)
        {
            maxnn=max(maxnn,getmax(x*2+1,mid+1,r,L,R));
        }

        return maxnn;
    }
}
//--------------------------------------------------------------------------
void update(ll x,ll l,ll r,ll T,ll k) {
    if(l==T&&r==T) 
    {
        lazy[x]=k;
        ans[x]=k;
        maxn[x]=k;
    } 
    else 
    {
        ll mid=(l+r)/2;
        if(lazy[x])
            push_down(x,r-l+1);
        if(T<=mid) 
        {
            update(x*2,l,mid,T,k);
        }
        if(T>mid) 
        {
            update(x*2+1,mid+1,r,T,k);
        }
        ans[x]=(ans[x*2]+ans[x*2+1]);
        maxn[x]=max(maxn[x*2],maxn[x*2+1]);
    }
}
ll qnum(ll x,ll y) 
{
    ll sum=0;
    while(ltop[x]!=ltop[y]) 
    {
        if(deep[ltop[x]]<deep[ltop[y]]) 
        {
            swap(x,y);
        }
        kkk=0;
        getsum(1,1,n,id[ltop[x]],id[x]);
        sum+=kkk;
        x=fa[ltop[x]];
    }
    if(deep[x]>deep[y]) 
    {
        swap(x,y);
    }
    kkk=0;
    getsum(1,1,n,id[x],id[y]);
    sum+=kkk;
    return sum;
}
ll qmax(ll x,ll y)
{
    ll maxnq=-1;
    while(ltop[x]!=ltop[y])
    {
        if(deep[ltop[x]]<deep[ltop[y]])
        {
            swap(x,y);
        }
        maxnq=max(maxnq,getmax(1,1,n,id[ltop[x]],id[x]));
        x=fa[ltop[x]];
    }
    if(deep[x]>deep[y])
    {
        swap(x,y);
     }
     maxnq=max(maxnq,getmax(1,1,n,id[x],id[y]));
     return maxnq;
}
void change(ll a,ll b)
{
    update(1,1,n,a,b);
}
//----------------------------------------------------------------------
void dfs1(ll x,ll father,ll dep) 
{
    deep[x]=dep;
    fa[x]=father;
    siz[x]=1;
    ll heavyson=-1;
    for(ll i=head[x]; i; i=e[i].next) 
    {
        ll y=e[i].to;
        if(y==father) 
        {
            continue;
        }
        dfs1(y,x,dep+1); 
        siz[x]+=siz[y];
        if(siz[y]>heavyson) 
        {
            heavyson=siz[y];
            son[x]=y;
        }
    }
}
void dfs2(ll x,ll top) 
{
    id[x]=++tot;
    w2[tot]=w[x];
    ltop[x]=top;
    if(son[x]==0)
        return ;
    dfs2(son[x],top);
    for(ll i=head[x]; i; i=e[i].next) 
    {
        ll y=e[i].to;
        if(y!=fa[x]&&y!=son[x]) 
        {
            dfs2(y,y);
        }
    }
}
int main() {
    cin>>n;
    for(ll i=1; i<n; i++) 
    {
        cin>>a>>b;
        add(a,b);
        add(b,a);
    }
    for(ll i=1; i<=n; i++) 
    {
        cin>>w[i];
    }
    dfs1(1,0,1);
    dfs2(1,1);
    build(1,1,n);
    cin>>q;
    while(q--) 
    {
        cin>>k>>a>>b;
        if(k=="CHANGE") 
        {
            change(a,b);
        } 
        else if(k=="QMAX") 
        {
            cout<<qmax(a,b)<<endl;
        } 
        else
        {
            cout<<qnum(a,b)<<endl;
        } 
    }
    return 0;
}