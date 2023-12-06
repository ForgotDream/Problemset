/**
 * @file    P5068 [Ynoi2015] 我回来了.cpp
 * @author  ForgotDream
 * @brief   BIT + ST
 * @date    2023-12-04
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

constexpr int N = 1e5 + 50, M = 1e6 + 50;
int n, m, a[N], l[M], r[M];
std::vector<int> vec[M];
struct BIT {
  int tree[N];
  void modify(int u, int val) {
    for (int i = u; i <= n; i += i & -i) tree[i] += val;
  }
  int query(int u) {
    int res = 0;
    for (int i = u; i; i -= i & -i) res += tree[i];
    return res;
  }
  int query(int l, int r) { return query(r) - query(l - 1); }
} bit;
struct ST {
  int st[20][N];
  void init() {
    for (int i = 1; i <= n; i++) st[0][i] = a[i];
    for (int i = 1; i <= std::__lg(n); i++) {
      for (int j = 1; j <= n - (1 << i) + 1; j++) {
        st[i][j] = std::min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  int query(int l, int r) {
    int d = std::__lg(r - l + 1);
    return std::min(st[d][l], st[d][r - (1 << d) + 1]);
  }
} st;
void solve() {
  fin >> n >> m;
  for (int i = 1; i <= n; i++) a[i] = m + 1;
  for (int opt, i = 1; i <= m; i++) {
    fin >> opt;
    if (opt == 1) {
      int h = fin.read();
      a[h] = std::min(a[h], i);
    } else {
      fin >> l[i] >> r[i];
    }
  }
  // for (int i = 1; i <= n; i++) std::cout << a[i] << " \n"[i == n];
  st.init();
  for (int i = 1; i <= n; i++) {
    bit.modify(i, 1);
    int lst = 0;
    for (int j = 1; j <= n; j += i) {
      lst = std::max(lst, st.query(j, std::min(n, j + i - 1)));
      vec[lst].push_back(i);
    }
  }
  for (int i = 1; i <= m; i++) {
    for (auto j : vec[i]) bit.modify(j, 1);
    if (l[i]) fout << bit.query(l[i], r[i]) << "\n";
  }
}

int main() {
  // std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
