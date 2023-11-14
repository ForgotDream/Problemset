/**
 * @file    CF1794E Labeling the Tree with Distances.cpp
 * @author  ForgotDream
 * @brief   DP + Hash 
 * @date    2023-11-11
 */
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <set>
#include <vector>

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

template<i64 MOD>
struct ModInt {
  i64 val;
  explicit operator i64() { return val; }
  ModInt(i64 v = 0) : val(v % MOD) {}
  bool operator==(const ModInt<MOD> &rhs) const { return val == rhs.val; }
  bool operator!=(const ModInt<MOD> &rhs) const { return !(val == rhs.val); }
  bool operator<(const ModInt<MOD> &rhs) const { return val < rhs.val; }
  bool operator>(const ModInt<MOD> &rhs) const { return !(*this < rhs) && !(*this == rhs); }
  ModInt<MOD> &operator+=(const ModInt<MOD> &rhs) {
    val = (val + rhs.val) % MOD;
    return *this;
  }
  ModInt<MOD> &operator-=(const ModInt<MOD> &rhs) {
    val = (val - rhs.val + MOD) % MOD;
    return *this;
  }
  ModInt<MOD> &operator*=(const ModInt<MOD> &rhs) {
    val = (val * rhs.val) % MOD;
    return *this;
  }
  ModInt<MOD> &operator++() { return *this += 1; }
  ModInt<MOD> &operator--() { return *this -= 1; }
  ModInt<MOD> operator++(int) {
    auto cur = *this;
    ++(*this);
    return cur;
  }
  ModInt<MOD> operator--(int) {
    auto cur = *this;
    --(*this);
    return cur;
  }
  friend ModInt<MOD> operator+(const ModInt<MOD> &lhs, const ModInt<MOD> &rhs) {
    return ModInt<MOD>((lhs.val + rhs.val) % MOD);
  }
  friend ModInt<MOD> operator-(const ModInt<MOD> &lhs, const ModInt<MOD> &rhs) {
    return ModInt<MOD>((lhs.val - rhs.val + MOD) % MOD);
  }
  friend ModInt<MOD> operator*(const ModInt<MOD> &lhs, const ModInt<MOD> &rhs) {
    return ModInt<MOD>((lhs.val * rhs.val) % MOD);
  }
};

constexpr int N = 2e5 + 50;
constexpr i64 base = 20200721;
int n, a[N];
std::vector<int> adj[N];
ModInt<int(1e9 + 9)> pw1[N], f1[N], g1[N], lsh1, s1[N];
ModInt<int(1e9 + 7)> pw2[N], f2[N], g2[N], lsh2, s2[N];
std::set<ModInt<int(1e9 + 9)>> st1;
std::set<ModInt<int(1e9 + 7)>> st2;
void init() {
  pw1[0] = 1, pw2[0] = 1;
  st1.insert(1), st2.insert(1);
  for (int i = 1; i <= n; i++) {
    pw1[i] = pw1[i - 1] * base;
    pw2[i] = pw2[i - 1] * base;
    st1.insert(pw1[i]), st2.insert(pw2[i]);
  }
}
void dfs1(int u, int frm) {
  f1[u] = 1, f2[u] = 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs1(v, u);
    f1[u] += pw1[1] * f1[v], s1[u] += f1[v];
    f2[u] += pw2[1] * f2[v], s2[u] += f2[v];
  }
}
void dfs2(int u, int frm) {
  g1[u] = g1[frm] * pw1[1] + (s1[frm] - f1[u]) * pw1[2];
  g2[u] = g2[frm] * pw2[1] + (s2[frm] - f2[u]) * pw2[2];
  if (u != 1) g1[u] += pw1[1], g2[u] += pw2[1];
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs2(v, u);
  }
}
void solve() {
  fin >> n, init();
  for (int i = 1; i < n; i++) {
    fin >> a[i];
    lsh1 += pw1[a[i]], lsh2 += pw2[a[i]];
  }
  for (int i = 1, u, v; i < n; i++) {
    fin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs1(1, 0);
  s1[0] = f1[1], s2[0] = f2[1];
  dfs2(1, 0);
  std::vector<int> ans;
  // fout << lsh << "\n";
  for (int i = 1; i <= n; i++) {
    auto c1 = f1[i] + g1[i];
    auto c2 = f2[i] + g2[i];
    if (st1.count(c1 - lsh1) && st2.count(c2 - lsh2)) ans.push_back(i);
  }
  fout << ans.size() << "\n";
  for (auto i : ans) fout << i << " ";
  fout << "\n";
}

int main() {
  int t = 1;
  // fin >> t;
  while (t--) solve();
  return 0;
}
