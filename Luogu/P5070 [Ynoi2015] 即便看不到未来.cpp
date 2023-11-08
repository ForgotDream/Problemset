/**
 * @file    P5070 [Ynoi2015] 即便看不到未来.cpp
 * @author  ForgotDream
 * @brief   BIT
 * @date    2023-11-07
 */
#include <algorithm>
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
FastIO::os fout;
#pragma endregion

using i64 = long long;

constexpr int N = 1e6 + 50, M = 12;
int n, m, a[N], pre[N];
struct Query {
  int l, r, id;
  Query() = default;
  Query(int l, int r, int id) : l(l), r(r), id(id) {}
};
std::vector<Query> q[N];
struct BIT {
  int tree[N];
  void modify(int u, int val) {
    for (int i = u; i <= n; i += i & -i) tree[i] += val;
  }
  void modify(int l, int r, int val) {
    modify(l, val), modify(r + 1, -val);
  }
  int query(int u) {
    int res = 0;
    for (int i = u; i; i -= i & -i) res += tree[i];
    return res % 10;
  }
} bit[M];
struct Num {
  int pos, val;
  bool operator<(const Num &rhs) const { return pos < rhs.pos; }
} st[N];
int top = 0;
bool vis[N];
int ans[N][M];
void solve() {
  fin >> n >> m;
  int mx = 0;
  for (int i = 1; i <= n; i++) fin >> a[i], mx = std::max(mx, a[i]);
  for (int i = 1, l, r; i <= m; i++) {
    fin >> l >> r;
    q[r].emplace_back(l, r, i);
  }
  for (int i = 1; i <= n; i++) {
    top = 0, st[++top] = {i, a[i]};
    int lo = std::max(1, a[i] - 11), hi = std::min(mx, a[i] + 11);
    for (int j = lo; j <= hi; j++) {
      vis[j] = false;
      if (pre[j]) st[++top] = {pre[j], j};
    }
    std::sort(st + 1, st + top + 1);
    int s = a[i], t = a[i];
    for (int j = top; j && st[j].pos > pre[a[i]]; j--) {
      vis[st[j].val] = true;
      while (vis[s - 1] && s - 1 >= lo) s--;
      while (vis[t + 1] && t + 1 <= hi) t++;
      bit[a[i] - s].modify(st[j - 1].pos + 1, st[j].pos, -1);
      bit[t - a[i]].modify(st[j - 1].pos + 1, st[j].pos, -1);
      if (t - s + 1 <= 10) bit[t - s + 1].modify(st[j - 1].pos + 1, st[j].pos, 1);
    }
    pre[a[i]] = i;
    for (auto [l, r, id] : q[i]) {
      for (int j = 1; j <= 10; j++) ans[id][j] = bit[j].query(l);
    }
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= 10; j++) fout.pc(ans[i][j] + '0');
    fout.pc('\n');
  }
}

int main() {
  // std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // fin >> t;
  while (t--) solve();
  return 0;
}
