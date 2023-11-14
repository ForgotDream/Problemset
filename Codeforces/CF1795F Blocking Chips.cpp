/**
 * @file    CF1795F Blocking Chips.cpp
 * @author  ForgotDream
 * @brief   Binary Search
 * @date    2023-11-11
 */
#include <bits/stdc++.h>

#pragma region
namespace FastIO {/*{{{*/
static constexpr signed bufsize = 1 << 18;
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

using i64 = int64_t;
using u64 = uint64_t;

constexpr int N = 2e5 + 50;
int n, k, a[N];
std::vector<int> adj[N];
int dep[N], need[N];
bool vis[N];
bool dfs(int u, int frm) {
  dep[u] = 0;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    if (!dfs(v, u)) return false;
    if (!vis[v]) dep[u] = std::max(dep[u], dep[v] + 1);
  }
  if (dep[u] >= need[u]) return true;
  if (!frm || vis[frm]) return false;
  vis[frm] = true, need[frm] = need[u] - 1, need[u] = 0;
  return true;
}
bool check(int u) {
  for (int i = 1; i <= n; i++) vis[i] = false, need[i] = 0;
  for (int i = 1; i <= k; i++) need[a[i]] = u / k + (i <= u % k), vis[a[i]] = true;
  return dfs(1, 0);
}
void solve() {
  fin >> n;
  for (int i = 1; i <= n; i++) adj[i].clear();
  for (int i = 1, u, v; i < n; i++) {
    fin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  fin >> k;
  for (int i = 1; i <= k; i++) fin >> a[i];
  int lo = 0, hi = n, ans = 0;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    if (check(mid)) lo = mid + 1, ans = mid;
    else hi = mid - 1;
  }
  fout << ans << "\n";
}

int main() {
  int t = 1;
  fin >> t;
  while (t--) solve();
  return 0;
}
