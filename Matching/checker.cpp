#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
#define N 4000003
#define ls son[u][0]
#define rs son[u][1]
#define reg register
#define ll long long
#define p 1000000007
#define mid ((l+r)>>1)
using namespace std;

inline void read(int &x){
    x = 0;
    char c = getchar();
    while(c<'0'||c>'9') c = getchar();
    while(c>='0'&&c<='9'){
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
}

void print(int x){
	if(x>9) print(x/10);
	putchar(x%10+'0');
}

inline int add(int x,int y){
    return x+y>=p?x+y-p:x+y;
}

int a[N],son[N][2],siz[N];
int sum[N],taga[N],tagc[N],b[300003];
bool rev[N];
int n,q,rt,cnt,tp;

inline int neww(int x){
    int u = ++cnt;
	siz[u] = 1;
    a[u] = sum[u] = x;
    tagc[u] = -1;
    ls = rs = taga[u] = rev[u] = 0;
    return cnt;
}

inline int copy(int u){
    int v = ++cnt;
    a[v] = a[u],sum[v] = sum[u];
    son[v][0] = ls,son[v][1] = rs;
    rev[v] = rev[u];
    siz[v] = siz[u];
    taga[v] = taga[u];
    tagc[v] = tagc[u];
    return v;
}

inline void pushup(int u){
    siz[u] = siz[ls]+siz[rs]+1;
    sum[u] = add(add(sum[ls],sum[rs]),a[u]);
}

inline void pushr(int u){
    swap(ls,rs);
    rev[u] ^= 1;
}

inline void pusha(int u,int k){
    a[u] = add(a[u],k);
    taga[u] = add(taga[u],k);
    sum[u] = (sum[u]+(ll)siz[u]*k)%p;
}

inline void pushc(int u,int k){
    taga[u] = 0;
    tagc[u] = a[u] = k;
    sum[u] = (ll)siz[u]*k%p;
}

inline void pushdown(int u){
    if(tagc[u]!=-1||taga[u]||rev[u]){
        if(ls) ls = copy(ls);
        if(rs) rs = copy(rs);
    }
    if(tagc[u]!=-1){
        if(ls) pushc(ls,tagc[u]);
        if(rs) pushc(rs,tagc[u]);
        tagc[u] = -1;
    }
    if(taga[u]){
        if(ls) pusha(ls,taga[u]);
        if(rs) pusha(rs,taga[u]);
        taga[u] = 0;
    }
    if(!rev[u]) return;
    if(ls) pushr(ls);
    if(rs) pushr(rs);
    rev[u] = 0;
}

int merge(int u,int v){
    if(!u||!v) return u|v;
    if(rand()%(siz[u]+siz[v])<siz[u]){
        pushdown(u),u = copy(u);
        son[u][1] = merge(son[u][1],v);
        pushup(u);
        return u;
    }else{
        pushdown(v),v = copy(v);
        son[v][0] = merge(u,son[v][0]);
        pushup(v);
        return v;
    }
}

int merge1(int u,int v){
    if(!u||!v) return u|v;
    if(rand()%(siz[u]+siz[v])<siz[u]){
        son[u][1] = merge1(son[u][1],v);
        pushup(u);
        return u;
    }else{
        son[v][0] = merge1(u,son[v][0]);
        pushup(v);
        return v;
    }
}

void split(int cur,int k,int &u,int &v){
    if(!cur){
        u = v = 0;
        return;
    }
    pushdown(cur);
    if(siz[son[cur][0]]<k){
        u = copy(cur);
        split(son[u][1],k-siz[son[u][0]]-1,son[u][1],v);
        pushup(u);
    }else{
        v = copy(cur);
        split(son[v][0],k,u,son[v][0]);
        pushup(v);
    }
}

inline void reverse(int l,int r){
    int x,y,z;
    split(rt,l-1,x,y);
    split(y,r-l+1,y,z);
    y = copy(y);
    pushr(y);
    rt = merge(merge(x,y),z);
}

inline void change(int l,int r,int k){
    int x,y,z;
    split(rt,l-1,x,y);
    split(y,r-l+1,y,z);
    y = copy(y);
    pushc(y,k);
    rt = merge(merge(x,y),z);
}

inline void modify(int l,int r,int k){
    int x,y,z;
    split(rt,l-1,x,y);
    split(y,r-l+1,y,z);
    y = copy(y);
    pusha(y,k);
    rt = merge(merge(x,y),z);
}

inline void swap(int l1,int r1,int l2,int r2){
    int v,w,x,y,z;
    if(l1>l2){
        swap(l1,l2);
        swap(r1,r2);
    }
    split(rt,l1-1,v,w);
    split(w,r1-l1+1,w,x);
    split(x,l2-r1-1,x,y);
    split(y,r2-l2+1,y,z);
    rt = merge(merge(merge(merge(v,y),x),w),z);
}

inline void paste(int l1,int r1,int l2,int r2){
    bool flag = false;
    int v,w,x,y,z;
    if(l1>l2){
        swap(l1,l2);
        swap(r1,r2);
        flag = true;
    }
    split(rt,l1-1,v,w);
    split(w,r1-l1+1,w,x);
    split(x,l2-r1-1,x,y);
    split(y,r2-l2+1,y,z);
    if(flag) w = copy(y);
    else y = copy(w);
    rt = merge(merge(merge(merge(v,w),x),y),z);
}

inline int query(int l,int r){
    int x,y,z,res;
    split(rt,l-1,x,y);
    split(y,r-l+1,y,z);
    res = sum[y];
    rt = merge(merge(x,y),z);
    return res;
}

void dfs(int u){
    pushdown(u);
    if(ls) dfs(ls);
    b[++tp] = a[u];
    if(rs) dfs(rs);
}

int build(int l,int r){
	if(l>r) return 0;
	int u = neww(b[mid]);	
	ls = build(l,mid-1);
	rs = build(mid+1,r);
	pushup(u);
	return u;
}

int main(){
    srand(time(0));
    int op,l1,r1,l2,r2,k;
    read(n),read(q);
    for(reg int i=1;i<=n;++i) read(b[i]);
    rt = build(1,n);
    while(q--){
        read(op),read(l1),read(r1);
        if(op==1){
        	print(query(l1,r1));
        	putchar('\n');
		}else if(op==2){
            read(k);
            change(l1,r1,k);
        }else if(op==3){
            read(k);
            modify(l1,r1,k);
        }else if(op==4){
            read(l2),read(r2);
            paste(l1,r1,l2,r2);
        }else if(op==5){
            read(l2),read(r2);
            swap(l1,r1,l2,r2);
        }else reverse(l1,r1);
        if(cnt>3600000){
        	tp = 0;
        	dfs(rt);
        	rt = cnt = 0;
        	rt = build(1,n);
		}
    }
    tp = 0;
    dfs(rt);
    for(reg int i=1;i<=n;++i) print(b[i]),putchar(' ');
  putchar('\n');
    return 0;
}
