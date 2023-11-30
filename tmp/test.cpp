#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <algorithm>  
#include <queue>  
  
using namespace std;  
const int Maxn = 0x3f3f3f3f;  
const int N = 1005, M = 6005, L = 1 << 10;  
int lst[N], f[N][L], nxt[M], to[M], cst[M], g[L], c[12];   
int n, m, k, T, Cn; bool vis[N];  
queue<int> Q;  
  
template <class T> inline T Min(const T a, const T b) {return a < b? a : b;}  
template <class T> inline void CkMin(T &a, const T b) {if (a > b) a = b;}  
  
struct point  
{  
    int col, id;  
    #define col(x) a[x].col  
    #define id(x) a[x].id  
}a[12];  
  
inline bool cmp(const point x, const point y) {return x.col < y.col;}  
  
inline int get()  
{  
    char ch; bool f = false; int res = 0;  
    while (((ch = getchar()) < '0' || ch > '9') && ch != '-');  
    if (ch == '-') f = true;  
     else res = ch - '0';  
    while ((ch = getchar()) >='0' && ch <= '9')  
        res = (res << 3) + (res << 1) + ch - '0';  
    return f? ~res + 1 : res;  
}  
  
inline void put(int x)  
{  
    if (x < 0)  
      x = ~x + 1, putchar('-');  
    if (x > 9) put(x / 10);  
    putchar(x % 10 + 48);  
}  
  
inline void add(const int x, const int y, const int z)  
{  
    nxt[++T] = lst[x]; lst[x] = T; to[T] = y; cst[T] = z;  
    nxt[++T] = lst[y]; lst[y] = T; to[T] = x; cst[T] = z;  
}  
  
inline void SPFA(const int I)  
{  
    int x, y;  
    while (!Q.empty())  
    {  
        x = Q.front(); vis[x] = false; Q.pop();  
        for (int i = lst[x]; i; i = nxt[i])  
         if (f[y = to[i]][I] > f[x][I] + cst[i])  
         {  
            f[y][I] = f[x][I] + cst[i];  
            if (!vis[y]) vis[y] = true, Q.push(y);  
         }  
    }  
}  
  
inline int solve(const int cnt)  
{  
    int Cm = 1 << cnt;  
    for (int i = 1; i < Cm; ++i)  
    {  
        for (int j = 1; j <= n; ++j)  
        {  
            for (int k = (i - 1) & i; k; k = (k - 1) & i)  
            // 表示枚举子集：k不断减一就不会遗漏  
            // (k - 1) & i 表示状态 k 中包含的关键点总状态 i 中一定包含    
             CkMin(f[j][i], f[j][k] + f[j][i - k]);  
            if (f[j][i] != Maxn) vis[j] = true, Q.push(j);  
        }  
        SPFA(i);  
    }  
    int res = Maxn;  
    for (int i = 1; i <= n; ++i) CkMin(res, f[i][Cm - 1]);  
    return res;  
}  
  
int main()  
{   
    n = get(); m = get(); k = get(); int x, y;  
    for (int i = 1; i <= m; ++i)  
    {  
        x = get(); y = get();   
        add(x, y, get());  
    }  
    for (int i = 1; i <= k; ++i)   
        col(i) = get(), id(i) = get();  
    sort(a + 1, a + k + 1, cmp);  
    for (int i = 1; i <= k; ++i)  
    {  
        if (col(i) != col(i - 1)) Cn++; c[i] = Cn;  
    }  
    for (int i = 1; i <= k; ++i) col(i) = c[i]; //离散化 
    Cn = (1 << Cn);  
    memset(g, Maxn, sizeof(g));  
    for (int i = 1; i < Cn; ++i)  
    {  
        memset(f, Maxn, sizeof(f));  
        int cnt = 0;   
        for (int j = 1; j <= k; ++j)   
         if ((1 << col(j) - 1) & i) f[id(j)][1 << cnt++] = 0;  
        g[i] = solve(cnt);  
     }   
    for (int i = 1; i < Cn; ++i)  
     for (int j = (i - 1) & i; j; j = (j - 1) & i)  
      CkMin(g[i], g[j] + g[i - j]);  
    return put(g[Cn - 1]), 0;  
}  
