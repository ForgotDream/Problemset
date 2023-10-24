/**
 * @file    P3920 [WC2014] 紫荆花之恋.cpp
 * @author  ForgotDream
 * @brief   点分树 + 根号重构 + 替罪羊
 * @date    2023-09-10
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#pragma region
struct FastIO {
static constexpr signed bufsize = 1 << 18;
char inbuf[bufsize], *p1 = inbuf, *p2 = inbuf;
char outbuf[bufsize], *pp = outbuf;
~FastIO() { flush(); }
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
FastIO &operator>>(T &rhs) { return read(rhs), *this; }
FastIO &operator>>(char *rhs) { return read(rhs), *this; }
template <typename T>
FastIO &operator<<(const T &rhs) { return print(rhs), *this; }
} fin, fout;
#pragma endregion

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 1e5 + 50, M = 350;
constexpr double alpha = 0.8;
int n, a[N], ignore;
std::vector<pii> adj[N];
std::vector<int> blk[N], d[N], fa[N];
struct QuasiBST {  // Simulate BST in O(n \sqrt n) time
  std::vector<int> big, small;
  void sort() { std::sort(big.begin(), big.end()); }
  void clear() { big.clear(), small.clear(); }
  int calc(int val) {
    if (small.size() > M) {
      std::vector<int> tmp(big.size() + small.size());
      std::sort(small.begin(), small.end());
      std::merge(big.begin(), big.end(), small.begin(), small.end(),
                 tmp.begin());
      big = tmp, small.clear();
    }
    int res = std::upper_bound(big.begin(), big.end(), val) - big.begin();
    for (const auto &i : small) res += i <= val;
    small.push_back(-val);
    return res;
  }
} dis[N], ch[N];
int siz[N], max[N], sum, rt;
bool valid[N];
void calcsiz(int u, int frm) {
  siz[u] = 1, max[u] = 0;
  for (const auto &[v, w] : adj[u]) {
    if (v == frm || !valid[v]) continue;
    calcsiz(v, u);
    siz[u] += siz[v], max[u] = std::max(max[u], siz[v]);
  }
  max[u] = std::max(max[u], sum - siz[u]);
  if (max[u] < max[rt]) rt = u;
}
void calcdis(int u, int frm, int len) {
  if (!d[u].empty()) ch[rt].big.push_back(d[u].back() - a[u]);
  blk[rt].push_back(u), fa[u].push_back(rt);
  dis[rt].big.push_back(len - a[u]), d[u].push_back(len);
  for (const auto &[v, w] : adj[u]) {
    if (v == frm || !valid[v]) continue;
    calcdis(v, u, len + w);
  }
}
void dfz(int u) {
  valid[u] = false;
  calcdis(u, 0, 0);
  dis[u].sort(), ch[u].sort();
  for (const auto &[v, w] : adj[u]) {
    if (!valid[v]) continue;
    rt = 0, sum = siz[v], max[rt] = 1e9;
    calcsiz(v, 1);
    // std::cerr << u << " " << rt << "\n";
    dfz(rt);
  }
}
void rebuild(int u) {
  auto tmp = blk[u];
  for (const auto &i : tmp) {
    dis[i].clear(), ch[i].clear();
    blk[i].clear(), valid[i] = true;
    int p;
    do {
      p = fa[i].back();
      fa[i].pop_back(), d[i].pop_back();
    } while (p != u);
  }
  rt = 0, sum = tmp.size(), max[rt] = 1e9;
  calcsiz(u, 0), dfz(rt);
}
i64 ans;
void solve() {
  fin >> ignore >> n;
  fin >> ignore >> ignore >> a[1];
  fa[1].push_back(1), blk[1].push_back(1), d[1].push_back(0);
  dis[1].small.push_back(-a[1]);
  fout << ans << "\n";
  for (int i = 2, w, f; i <= n; i++) {
    fin >> f >> w >> a[i], f ^= ans % int(1e9);
    adj[f].emplace_back(i, w);
    adj[i].emplace_back(f, w);
    fa[i] = fa[f], d[i] = d[f];
    for (auto &j : d[i]) j += w;
    d[i].push_back(0), fa[i].push_back(i);
    for (int j = fa[i].size() - 1; ~j; j--) {
      blk[fa[i][j]].push_back(i);
      ans += dis[fa[i][j]].calc(a[i] - d[i][j]);
      if (j) ans -= ch[fa[i][j]].calc(a[i] - d[i][j - 1]);
    }
    for (int j = 0; j < fa[i].size() - 1; j++) {
      if (alpha * blk[fa[i][j]].size() < blk[fa[i][j + 1]].size()) {
        rebuild(fa[i][j]);
        break;
      }
    }
    fout << ans << "\n";
  }
}

signed main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}