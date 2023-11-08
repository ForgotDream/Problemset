/**
 * @file    CF1551F Equidistant Vertices.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-11-08
 */
#include <cstring>
#include <iostream>
#include <vector>

#pragma region
namespace FastIO {
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
  is &operator>>(T &rhs) {
    return read(rhs), *this;
  }
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
    do sta[top++] = x % 10, x /= 10;
    while (x);
    while (top) pc(sta[--top] + '0');
  }
  inline void print(const char *s) {
    for (; *s; ++s) pc(*s);
  }
  inline void print(char *s) {
    for (; *s; ++s) pc(*s);
  }
  inline void print(const std::string &s) {
    for (const auto &c : s) pc(c);
  }
  inline void print(const char &c) { pc(c); }
  inline void flush() { fwrite(outbuf, 1, pp - outbuf, stdout), pp = outbuf; }
  template <typename T>
  os &operator<<(const T &rhs) {
    return print(rhs), *this;
  }
};
}  // namespace FastIO
FastIO::is fin;
FastIO::os fout;
#pragma endregion

using i64 = long long;

constexpr int N = 105, mod = 1e9 + 7;
int n, k;
std::vector<int> adj[N];
i64 f[N], cnt;
void dfs(int u, int frm, int d) {
  if (d == 0) return cnt++, void();
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u, d - 1);
  }
}
void solve() {
  fin >> n >> k;
  for (int i = 1; i <= n; i++) adj[i].clear();
  for (int i = 1, u, v; i < n; i++) {
    fin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  if (k == 2) return fout << n * (n - 1) / 2 << "\n", void();
  i64 ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int t = 1; t <= n; t++) f[t] = 0;
      f[0] = 1;
      for (auto v : adj[j]) {
        cnt = 0;
        dfs(v, j, i - 1);
        for (int t = k; t >= 1; t--) f[t] = (f[t] + f[t - 1] * cnt) % mod;
      }
      ans = (ans + f[k]) % mod;
    }
  }
  fout << ans << "\n";
}

int main() {
  // std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  fin >> t;
  while (t--) solve();
  return 0;
}
