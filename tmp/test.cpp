#include <bits/stdc++.h>
#define rg register
using namespace std;
static char buf[1000000], *p1 = buf, *p2 = buf;
#define getchar()                                                         \
  p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) \
      ? EOF                                                               \
      : *p1++
inline void read(int &x) {
  int f = 1;
  x = 0;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') f = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    c = getchar();
  }
  x *= f;
}
inline void readl(long long &x) {
  int f = 1;
  x = 0;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') f = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    c = getchar();
  }
  x *= f;
}
//------------------上边是一大串快读------------------
const long long mod = 1e9;
const int maxn = 75005;
int head, tail;
long long k1, k2;
struct node {
  long long x, y;
  node(long long a = 0, long long b = 0) {
    x = a;
    y = b;
  }
  node operator+(const node a) const { return node(x + a.x, y + a.y); }
  node operator-(const node a) const { return node(x - a.x, y - a.y); }
};
struct yyy {
  int ls, rs;
  long long sum1, sum2;
} f[30000005];
int root[maxn], cnt;
inline int Update(int l, int r, int pre) {
  int rt = ++cnt;
  f[rt] = f[pre];
  if (l == r) {
    f[rt].sum1 += k1;
    f[rt].sum2 += k2;
    return rt;
  }
  f[rt].sum1 += k1;
  f[rt].sum2 += k2;
  int mid = l + r >> 1;
  if (head <= mid)
    f[rt].ls = Update(l, mid, f[rt].ls);
  else
    f[rt].rs = Update(mid + 1, r, f[rt].rs);
  return rt;
}
inline node Query(int l, int r, int rt) {
  if (head <= l && r <= tail) return node(f[rt].sum1, f[rt].sum2);
  int mid = l + r >> 1;
  node ans(0, 0);
  if (head <= mid) ans = ans + Query(l, mid, f[rt].ls);
  if (tail > mid) ans = ans + Query(mid + 1, r, f[rt].rs);
  return ans;
}
int main() {
  //	freopen("1.in","r",stdin);
  rg int i, x, y, xx, yy, a, b, n, m;
  rg long long last = 0, k;
  rg node ans;
  read(n);
  for (i = 1; i <= n; i++) {
    read(x);
    read(xx);
    read(y);
    read(a);
    read(b);
    read(yy);
    head = 0;
    k1 = 0;
    k2 = y;
    root[i] = Update(0, mod, root[i - 1]);
    head = x + 1;
    k1 = a;
    k2 = b - y;
    root[i] = Update(0, mod, root[i]);
    head = xx + 1;
    k1 = -a;
    k2 = yy - b;
    root[i] = Update(0, mod, root[i]);
  }
  read(m);
  for (i = 1; i <= m; i++) {
    node ans(0, 0);
    read(x);
    read(y);
    readl(k);
    k = (k + last) % mod;
    head = 0;
    tail = k;
    ans = ans + Query(0, mod, root[y]);
    if (x) head = 0, tail = k, ans = ans - Query(0, mod, root[x - 1]);
    last = ans.x * k + ans.y;
    printf("%lld\n", last);
  }
  return 0;
}
