/**
 * @file    CF1223E Paint the Tree.cpp
 * @author  ForgotDream
 * @brief   DP?
 * @date    2023-11-05
 */
#include <algorithm>
#include <iostream>
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

constexpr int N = 5e5 + 50;
int n, k;
std::vector<pii> adj[N];
i64 f[N][2];
void dfs(int u, int frm) {
  std::vector<i64> t;
  for (auto [v, w] : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
    f[u][1] += f[v][0], f[u][0] += f[v][0];
    t.emplace_back(f[v][1] + w - f[v][0]);
  }
  std::sort(t.begin(), t.end(), std::greater<>());
  for (int i = 0; i < std::min(k, int(t.size())); i++) {
    if (t[i] < 0) break;
    if (i != k - 1) f[u][1] += t[i];
    f[u][0] += t[i];
  }
}
void solve() {
  fin >> n >> k;
  for (int i = 1; i <= n; i++) adj[i].clear(), f[i][0] = f[i][1] = 0;
  for (int i = 1, u, v, w; i < n; i++) {
    fin >> u >> v >> w;
    adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
  }
  dfs(1, 0);
  fout << std::max(f[1][0], f[1][1]) << "\n";
}

int main() {
  // std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  fin >> t;
  while (t--) solve();
  return 0;
}
