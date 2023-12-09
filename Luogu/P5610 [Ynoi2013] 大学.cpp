/**
 * @file    P5610 [Ynoi2013] 大学.cpp
 * @author  ForgotDream
 * @brief   BIT + DSU + Math
 * @date    2023-12-08
 */
#include <bits/stdc++.h>

#pragma region
namespace FastIO {/*{{{*/
static constexpr signed bufsize = 1 << 20;
struct is {
  char inbuf[bufsize], *p1 = inbuf, *p2 = inbuf;
  inline char gc() {
    if (p1 == p2) p1 = inbuf, p2 = inbuf + fread(inbuf, 1, bufsize, stdin);
    return p1 == p2 ? EOF : *p1++;
  }
  template <typename T>
  inline void read(T &x) {
    x = 0;
    T f = 1;
    char c = gc();
    while (c < '0' || c > '9') f = ( c == '-' ? -f : f), c = gc();
    while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = gc();
    x *= f;
  }
  inline void read(char *s) {
    char c = gc();
    while (c == ' ' || c == '\n' || c == '\r') c = gc();
    while (c != ' ' && c != '\n' && c != '\r') *s++ = c, c = gc();
  }
  inline void read(char &c) {
    c = gc();
    while (c == ' ' || c == '\n' || c == '\r') c = gc();
  }
  inline void read(std::string &s) {
    std::string().swap(s);
    char c = gc();
    while (c == ' ' || c == '\n' || c == '\r') c = gc();
    while (c != ' ' && c != '\n' && c != '\r') s += c, c = gc();
  }
  template <typename T = int>
  inline T read() {
    T res;
    read(res);
    return res;
  }
  template <typename T>
  is &operator>>(T &rhs) { return read(rhs), *this; }
  is &operator>>(char *rhs) { return read(rhs), *this; }
};
struct os {
  char outbuf[bufsize], *pp = outbuf;
  ~os() { flush(); }
  inline void pc(const char &c) {
    if (pp - outbuf == bufsize) fwrite(outbuf, 1, bufsize, stdout), pp = outbuf;
    *pp++ = c;
  }
  template <typename T>
  inline void print(T x) {
    if (x < 0) x = -x, pc('-');
    static T sta[35];
    T top = 0;
    do sta[top++] = x % 10, x /= 10; while (x);
    while (top) pc(sta[--top] + '0');
  }
  inline void print(const char *s) { for (; *s; ++s) pc(*s); }
  inline void print(char *s) { for (; *s; ++s) pc(*s); }
  inline void print(const std::string &s) { for (const auto &c : s) pc(c); }
  inline void print(const char &c) { pc(c); }
  inline void flush() { fwrite(outbuf, 1, pp - outbuf, stdout), pp = outbuf; }
  template <typename T>
  os &operator<<(const T &rhs) { return print(rhs), *this; }
};
}  // namespace FastIO
FastIO::is fin;
FastIO::os fout;/*}}}*/
#pragma endregion

using i64 = int64_t;

constexpr int N = 1e5 + 50, M = 5e5 + 50;
int n, m, a[N];
struct BIT {
  i64 tree[M];
  void modify(int u, int val) {
    for (int i = u; i <= n; i += i & -i) tree[i] += val;
  }
  i64 query(int u) {
    i64 res = 0;
    for (int i = u; i; i -= i & -i) res += tree[i];
    return res;
  }
} bit;
struct DSU {
  int *fa;
  void init(int n) { std::iota(fa, fa + n, 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
} dsu[M];
int *p[M], pool[400 * N], *pivot = pool, cnt[M];
void modify(int l, int r, int v) {
  if (v == 1) return;
  l = std::lower_bound(p[v], p[v] + cnt[v], l) - p[v];
  r = std::upper_bound(p[v], p[v] + cnt[v], r) - p[v] - 1;
  if (l > r) return;
  for (int i = dsu[v].find(l); i <= r;) {
    int f = p[v][i];
    if (a[f] % v == 0) bit.modify(f, a[f] / v - a[f]), a[f] /= v;
    if (i >= r) break;
    if (a[f] % v) i = dsu[v].fa[i] = dsu[v].find(i + 1);
    else i = dsu[v].find(i + 1);
  }
}
void solve() {
  fin >> n >> m;
  for (int i = 1; i <= n; i++) fin >> a[i], cnt[a[i]]++, bit.modify(i, a[i]);
  int mx = *std::max_element(a + 1, a + n + 1);
  for (int i = 1; i <= mx; i++) {
    for (int j = 2 * i; j <= mx; j += i) cnt[i] += cnt[j];
  }
  for (int i = 1; i <= mx; i++) {
    if (!cnt[i]) continue;
    dsu[i].fa = pivot, pivot += cnt[i], dsu[i].init(cnt[i]);
    p[i] = pivot, pivot += cnt[i], cnt[i] = 0;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j * j <= a[i]; j++) {
      if (a[i] % j != 0) continue;
      p[j][cnt[j]++] = i;
      if (j * j != a[i]) p[a[i] / j][cnt[a[i] / j]++] = i;
    }
  }
  i64 lst = 0;
  for (int opt, l, r; m; m--) {
    fin >> opt >> l >> r;
    l ^= lst, r ^= lst;
    if (opt == 1) modify(l, r, fin.read<int>() ^ lst);
    else fout << (lst = bit.query(r) - bit.query(l - 1)) << '\n';
  }
}

int main() {
  // std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
