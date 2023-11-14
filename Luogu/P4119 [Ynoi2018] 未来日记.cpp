/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-11-08
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>

#pragma region
namespace FastIO {/*{{{*/
static constexpr signed bufsize = 1 << 23;
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
    while (c < '0' || c > '9') f = (c == '-' ? -f : f), c = gc();
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

using i64 = long long;

// 忌：重构代码
constexpr int N = 1e5 + 50, M = 350, W = 1e5;
int n, m, a[N], mx;
struct Query {
  int opt, l, r, x, y;
} qry[N];
namespace SQRT {
int blk, bcnt, bln[N], lp[M], rp[M];
int vblk, vcnt, vbln[N];
// --- DSU ---
int fa[N];
inline int find(int u) {
  while (u != fa[u]) u = fa[u] = fa[fa[u]];
  return u;
}
// -----------
int bsum[M][M], vsum[M][N], cnt[M][N];
int rt[M][N];
// 这东西就纯纯的跟第二分块是一样的
inline int merge(int p, int u, int v) {
  if (rt[p][v]) fa[rt[p][u]] = rt[p][v];
  else rt[p][v] = rt[p][u], a[rt[p][u]] = v;
  int res = cnt[p][u];
  cnt[p][v] += cnt[p][u], cnt[p][u] = rt[p][u] = 0;
  return res;
}
void init() {
  // ----- 分块 -----
  blk = 1.5 * sqrt(n), bcnt = (n - 1) / blk + 1;
  for (int i = 1; i <= bcnt; i++) lp[i] = (i - 1) * blk + 1, rp[i] = i * blk;
  rp[bcnt] = n;
  for (int i = 1; i <= n; i++) bln[i] = (i - 1) / blk + 1;
  // ----------------
  // --- 值域分块 ---
  vblk = 1.5 * sqrt(mx), vcnt = (mx - 1) / vblk + 1;
  for (int i = 1; i <= mx; i++) vbln[i] = (i - 1) / vblk + 1;
  // ----------------
  for (int i = 1; i <= bcnt; i++) {
    for (int j = lp[i]; j <= rp[i]; j++) {
      if (rt[i][a[j]]) fa[j] = rt[i][a[j]];
      else rt[i][a[j]] = j;
      cnt[i][a[j]]++, bsum[i][vbln[a[j]]]++, vsum[i][a[j]]++;
    }
  }
  for (int i = 1; i <= bcnt; i++) {
    for (int j = 1; j <= vcnt; j++) bsum[i][j] += bsum[i - 1][j];
    for (int j = 1; j <= mx; j++) vsum[i][j] += vsum[i - 1][j];
  }
}
int s[M], top;
inline void bruteForce(int p, int l, int r, int bfr, int aft) {
  top = 0;
  for (int i = lp[p]; i <= rp[p]; i++) {
    a[i] = a[find(i)];
    if (a[i] == bfr || a[i] == aft) s[++top] = i;
  }
  int d = 0;
  for (int i = l; i <= r; i++) {
    if (a[i] == bfr) a[i] = aft, d++;
  }
  // rebuild
  rt[p][bfr] = rt[p][aft] = 0;
  for (int i = 1; i <= top; i++) fa[s[i]] = s[i];
  for (int i = 1; i <= top; i++) {
    if (rt[p][a[s[i]]]) fa[s[i]] = rt[p][a[s[i]]];
    else rt[p][a[s[i]]] = s[i];
  }
  // update the prefix sum
  cnt[p][bfr] -= d, cnt[p][aft] += d;
  for (int i = p; i <= bcnt; i++) {
    vsum[i][bfr] -= d, vsum[i][aft] += d;
    bsum[i][vbln[bfr]] -= d, bsum[i][vbln[aft]] += d;
  }
}
inline void modify(int l, int r, int bfr, int aft) {
  if (bln[l] == bln[r]) {
    bruteForce(bln[l], l, r, bfr, aft);
  } else {
    bruteForce(bln[l], l, rp[bln[l]], bfr, aft);
    bruteForce(bln[r], lp[bln[r]], r, bfr, aft);
    int d = 0;
    for (int i = bln[l] + 1; i < bln[r]; i++) {
      if (rt[i][bfr]) d += merge(i, bfr, aft);
      vsum[i][bfr] -= d, vsum[i][aft] += d;
      bsum[i][vbln[bfr]] -= d, bsum[i][vbln[aft]] += d;
    }
    for (int i = bln[r]; i <= bcnt; i++) {
      vsum[i][bfr] -= d, vsum[i][aft] += d;
      bsum[i][vbln[bfr]] -= d, bsum[i][vbln[aft]] += d;
    }
  }
}
int tbs[M], tvs[N];  // `t` stands for temp
inline int query(int l, int r, int k) {
  if (bln[l] == bln[r]) {
    for (int i = l; i <= r; i++) a[i] = a[find(i)];
    for (int i = l; i <= r; i++) tbs[vbln[a[i]]]++, tvs[a[i]]++;
    int p = 1;
    while (k > tbs[p]) k -= tbs[p], p++;
    p = (p - 1) * vblk + 1;
    while (k > tvs[p]) k -= tvs[p], p++;
    for (int i = l; i <= r; i++) tbs[vbln[a[i]]]--, tvs[a[i]]--;
    return p;
  } else {
    for (int i = l; i <= rp[bln[l]]; i++) a[i] = a[find(i)];
    // std::cerr << rp[bln[l]] << " " << lp[bln[r]] << "\n";
    for (int i = lp[bln[r]]; i <= r; i++) a[i] = a[find(i)];
    for (int i = l; i <= rp[bln[l]]; i++) tbs[vbln[a[i]]]++, tvs[a[i]]++;
    for (int i = lp[bln[r]]; i <= r; i++) tbs[vbln[a[i]]]++, tvs[a[i]]++;
    int p = 1;
    while (k > tbs[p] + bsum[bln[r] - 1][p] - bsum[bln[l]][p]) {
      k -= tbs[p] + bsum[bln[r] - 1][p] - bsum[bln[l]][p], p++;
    }
    p = (p - 1) * vblk + 1;
    while (k > tvs[p] + vsum[bln[r] - 1][p] - vsum[bln[l]][p]) {
      k -= tvs[p] + vsum[bln[r] - 1][p] - vsum[bln[l]][p], p++;
    }
    for (int i = l; i <= rp[bln[l]]; i++) tbs[vbln[a[i]]]--, tvs[a[i]]--;
    for (int i = lp[bln[r]]; i <= r; i++) tbs[vbln[a[i]]]--, tvs[a[i]]--;
    return p;
  }
}
}  // namespace SQRT
void solve() {
  fin >> n >> m;
  for (int i = 1; i <= n; i++) fin >> a[i], mx = std::max(mx, a[i]), SQRT::fa[i] = i;
  // SQRT::debug();
  for (int i = 1, opt, l, r, x, y; i <= m; i++) {
    // std::cerr << i << "\n";
    fin >> opt >> l >> r;
    if (opt == 1) {
      fin >> x >> y;
      if (x == y) continue;
      qry[i] = {opt, l, r, x, y};
      mx = std::max({mx, x, y});
    } else {
      fin >> x;  // bruh
      qry[i] = {opt, l, r, x, 0};
    }
    // SQRT::debug();
  }
  SQRT::init();
  for (int i = 1; i <= m; i++) {
    auto [opt, l, r, x, y] = qry[i];
    if (!opt) continue;
    if (opt == 1) SQRT::modify(l, r, x, y);
    else fout << SQRT::query(l, r, x) << '\n';
  }
}

int main() {
  int t = 1;
  // fin >> t;
  while (t--) solve();
  return 0;
}
