/**
 * @file    CF1748E Yet Another Array Counting Problem.cpp
 * @author  ForgotDream
 * @brief   DP + Divide ans Conquer
 * @date    2023-11-10
 */
#include <iostream>
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

using i64 = long long;

constexpr int N = 2e5 + 50, mod = 1e9 + 7;
int n, m, a[N];
std::vector<i64> f[N];
struct ST {
  int st[20][N];
  int cmp(int u, int v) { return a[u] < a[v] ? v : u; }
  void init() {
    for (int i = 1; i <= n; i++) st[0][i] = i;
    for (int i = 1; i <= std::__lg(n); i++) {
      for (int j = 1; j <= n - (1 << i) + 1; j++) {
        st[i][j] = cmp(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  int query(int l, int r) {
    int d = std::__lg(r - l + 1);
    return cmp(st[d][l], st[d][r - (1 << d) + 1]);
  }
} st;
int solve(int l, int r) {
  if (l > r) return 0;
  int mid = st.query(l, r);
  int s = solve(l, mid - 1), t = solve(mid + 1, r);
  for (int i = 1; i <= m; i++) {
    f[mid][i] = (f[mid][i - 1] + f[s][i - 1] * f[t][i] % mod) % mod;
  }
  return mid;
}
void solve() {
  fin >> n >> m;
  for (int i = 1; i <= n; i++) fin >> a[i], f[i].assign(m + 1, 0);
  f[0].assign(m + 1, 1);
  st.init();
  int p = solve(1, n);
  fout << f[p][m] << "\n";
}

int main() {
  int t = 1;
  fin >> t;
  while (t--) solve();
  return 0;
}
