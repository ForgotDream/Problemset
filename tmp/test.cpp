#include <bits/stdc++.h>

using namespace std;

// #define int long long
#define i64 long long
#define ull unsigned long long
#define ldb long double
#define db double
#define i128 __int128
#define up(a, b, c) for (int a = (b); a <= (c); a++)
#define dn(a, b, c) for (int a = (b); a >= (c); a--)
#define pii pair<int, int>
#define pdi pair<double, int>
#define pivi pair<int, vector<int> >
#define lc k << 1
#define rc k << 1 | 1
#define fi first
#define se second
#define endl '\n'
#define i16 short
#define eps 1e-8

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

const int N = 1e6 + 100, M = 1e6 + 100;
const int mod = 998244353;
const int inf = 1e9 + 7;
const ull uinf = 1e18 + 14;

int n, id;
int a[N];
struct Bit {
  int tr[M];
  inline void add(int x, int val) {
    if (x == 0) return;
    assert(x > 0);
    for (; x < n + 10; x += x & (-x)) tr[x] += val;
  }
  inline int sum(int x) {
    int res = 0;
    assert(x >= 0);
    for (; x; x -= x & (-x)) res += tr[x];
    return res;
  }
  inline void init() { memset(tr, 0, sizeof tr); }
} T;
int s[N], top;
int Lmin[N], Lmax[N], Rmin[N], Rmax[N];
int L[N], R[N];
struct node {
  int op, x, y, id;
} p[N << 1];
int cnt;
inline bool cmp(const node &aa, const node &bb) {
  if (aa.x != bb.x) return aa.x < bb.x;
  else if (aa.op != bb.op) return aa.op < bb.op;
  return aa.y < bb.y;
}
int ans1[N], ans2[N];
inline void solve2() {
  cnt = 0;
  up(i, 1, n) { p[++cnt] = {0, i, R[i] + 1, 0}; }
  up(i, 1, n) {
    if (L[i] < 1) continue;
    p[++cnt] = {1, L[i], i + 1, i};
  }
  stable_sort(p + 1, p + 1 + cnt, cmp);
  up(i, 1, cnt) {
    if (!p[i].op) T.add(p[i].y, 1);
    else ans2[p[i].id] += T.sum(p[i].y);
  }
}
signed main() {
  freopen("interval.in", "r", stdin);
  freopen("interval.out", "w", stdout);
  // fin.tie(nullptr)->sync_with_stdio(false);
  fin >> n >> id;
  up(i, 1, n) fin >> a[i];
  top = 0;
  up(i, 1, n) {
    while (top && a[s[top]] <= a[i]) top--;
    Lmax[i] = s[top];
    s[++top] = i;
  }
  top = 0;
  up(i, 1, n) {
    while (top && a[s[top]] >= a[i]) top--;
    Lmin[i] = s[top];
    s[++top] = i;
  }
  up(i, 1, n) L[i] = min(Lmax[i], Lmin[i]);
  top = 0;
  s[top] = n + 1;
  dn(i, n, 1) {
    while (top && a[s[top]] <= a[i]) top--;
    Rmax[i] = s[top];
    s[++top] = i;
  }
  top = 0;
  s[top] = n + 1;
  dn(i, n, 1) {
    while (top && a[s[top]] >= a[i]) top--;
    Rmin[i] = s[top];
    s[++top] = i;
  }
  up(i, 1, n) R[i] = max(Rmax[i], Rmin[i]);
  solve2();
  // solve1();
  cnt = 0;
  up(i, 1, n) { p[++cnt] = {0, n + 1 - i, n + 1 - L[i] + 1, 0}; }
  up(i, 1, n) {
    if (n + 1 - R[i] < 1) continue;
    p[++cnt] = {1, n + 1 - R[i], n + 1 - i + 1, i};
  }
  stable_sort(p + 1, p + 1 + cnt, cmp);
  T.init();
  up(i, 1, cnt) {
    if (!p[i].op) T.add(p[i].y, 1);
    else ans1[p[i].id] += T.sum(p[i].y);
  }
  up(i, 1, n) fout << ans1[i] << " \n"[i == n];
  up(i, 1, n) fout << ans2[i] << " \n"[i == n];
  return 0;
}
