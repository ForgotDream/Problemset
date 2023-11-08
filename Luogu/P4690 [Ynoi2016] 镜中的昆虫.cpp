/**
 * @file    P4690 [Ynoi2016] 镜中的昆虫.cpp
 * @author  ForgotDream
 * @brief   Sqrt + 颜色段均摊
 * @date    2023-11-05
 */
#include <cmath>
#include <cstring>
#include <iostream>
#include <set>
#include <map>
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

constexpr int N = 2e5 + 50, M = 350;
int n, m, a[N];
std::map<int, int> colMap;
int colCnt, f[N], lst[N];
int posBln[N];
namespace SQRT {
int l[M], r[M], bln[N];
int blk, bcnt;
struct Block {
  int s[M];
  void clear() { memset(s, 0, sizeof(s)); }
  void modify(int u, int val) {
    if (!posBln[u]) return;
    for (int i = posBln[u]; i <= bcnt; i++) s[i] += val;
  }
  int query(int u) { return s[posBln[u]]; }
} b[M];
void init() {
  blk = sqrt(n), bcnt = (n - 1) / blk + 1;
  for (int i = 1; i <= bcnt; i++) l[i] = (i - 1) * blk + 1, r[i] = i * blk;
  r[bcnt] = n;
  for (int i = 1; i <= n; i++) bln[i] = (i - 1) / blk + 1;
}
inline void clear() {
  for (int i = 1; i <= bcnt; i++) b[i].clear();
}
struct Query {
  int opt, l, r, val;
} q[N];
void rebuild(int u) {
  memset(posBln, 0, sizeof(posBln)), clear();
  for (int i = u; i <= std::min(m, u + blk - 1); i++) {
    if (q[i].opt == 1) continue;
    posBln[q[i].r + 1]++;
  }
  posBln[1]++, posBln[n + 1] = 0;
  for (int i = 1; i <= n; i++) posBln[i] += posBln[i - 1];
  for (int i = 1; i <= n; i++) b[bln[i]].s[posBln[f[i]]]++;
  for (int i = 1; i <= bcnt; i++) {
    for (int j = 2; j <= bcnt; j++) b[i].s[j] += b[i].s[j - 1];
  }
}
inline void modify(int u, int val) {
  if (!u) return;
  b[bln[u]].modify(f[u], -1);
  // std::cout << bln[u] << " " << f[u] << " " << posBln[f[u]] << "\n";
  f[u] = val;
  // std::cout << bln[u] << " " << f[u] << " " << posBln[f[u]] << "\n";
  b[bln[u]].modify(f[u], 1);
}
}  // namespace SQRT
namespace ODT {
struct Node {
  int l, r, val;
  Node() = default;
  Node(int l, int r, int val) : l(l), r(r), val(val) {}
  friend bool operator<(const Node &lhs, const Node &rhs) {
    return lhs.l < rhs.l;
  }
};
std::set<Node> tr;
std::set<Node> col[N];
inline void delcol(int l, int r, int val) {
  col[val].erase({l, r, val});
  Node lp = *std::prev(col[val].upper_bound({l, 0, val}));
  Node rp = *col[val].lower_bound({r, 0, val});
  SQRT::modify(r, r + 1), SQRT::modify(lp.r, rp.l);
}
inline void addcol(int l, int r, int val) {
  Node lp = *std::prev(col[val].upper_bound({l, 0, val}));
  Node rp = *col[val].lower_bound({r, 0, val});
  col[val].emplace(l, r, val);
  SQRT::modify(lp.r, l), SQRT::modify(r, rp.l);
}
auto split(int pos) {
  auto it = tr.lower_bound({pos, 0, 0});
  if (it != tr.end() && it->l == pos) return it;
  it--;
  int l = it->l, r = it->r, val = it->val;
  tr.erase(it);
  tr.emplace(l, pos - 1, val);
  col[val].erase({l, r, val});
  col[val].emplace(l, pos - 1, val), col[val].emplace(pos, r, val);
  return tr.emplace(pos, r, val).first;
}
void assign(int l, int r, int val) {
  auto end = split(r + 1), begin = split(l);
  for (auto it = begin; it != end;) {
    auto tmp = it;
    delcol(it->l, it->r, it->val);
    it++, tr.erase(tmp);
  }
  tr.emplace(l, r, val), addcol(l, r, val);
}
}  // namespace ODT
void solve() {
  fin >> n >> m;
  for (int i = 1; i <= n; i++) fin >> a[i];
  SQRT::init();
  for (int i = 1; i <= m; i++) {
    using SQRT::q;
    fin >> q[i].opt >> q[i].l >> q[i].r;
    if (q[i].opt == 1) fin >> q[i].val;
  }
  for (int i = 1; i <= n; i++) {
    if (colMap.find(a[i]) == colMap.end()) colMap[a[i]] = ++colCnt;
    ODT::col[colMap[a[i]]].emplace(i, i, colMap[a[i]]);
    ODT::tr.emplace(i, i, colMap[a[i]]);
  }
  for (int i = 1; i <= 2 * n; i++) {
    ODT::col[i].emplace(0, 0, i), ODT::col[i].emplace(n + 1, n + 1, i);
  }
  for (int i = n; i; i--) {
    int &d = lst[colMap[a[i]]];
    if (d) f[i] = d;
    else f[i] = n + 1;
    d = i;
  }
  for (int i = 1; i <= m; i++) {
    if (i % SQRT::blk == 1) SQRT::rebuild(i);
    auto [opt, l, r, val] = SQRT::q[i];
    // for (int j = 1; j <= n; j++) std::cout << f[j] << " \n"[j == n];
    // for (int j = 1; j <= n; j++) std::cout << posBln[j] << " \n"[j == n];
    // for (auto [l, v, val] : ODT::tr) std::cout << "#" << l << " " << r << " " << val << "\n";
    // std::cout << "\n";
    if (opt == 1) {
      if (colMap.find(val) == colMap.end()) colMap[val] = ++colCnt;
      ODT::assign(l, r, colMap[val]);
    } else {
      using SQRT::bln;
      int ans = r - l + 1;
      if (bln[l] == bln[r]) {
        for (int j = l; j <= r; j++) ans -= (f[j] <= r);
      } else {
        for (int j = l; j <= SQRT::r[bln[l]]; j++) ans -= (f[j] <= r);
        for (int j = SQRT::l[bln[r]]; j <= r; j++) ans -= (f[j] <= r);
        for (int j = bln[l] + 1; j < bln[r]; j++) ans -= SQRT::b[j].query(r);
      }
      fout << ans << "\n";
    }
  }
}

int main() {
  // std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
