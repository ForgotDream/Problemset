#include <bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int, int>
#define fi first
#define se second
#define power(x) ((x) * (x))
using namespace std;

namespace FastIO {
template <typename T = int>
inline T read() {
  T s = 0, w = 1;
  char c = getchar();
  while (!isdigit(c)) {
    if (c == '-') w = -1;
    c = getchar();
  }
  while (isdigit(c)) s = (s * 10) + (c ^ 48), c = getchar();
  return s * w;
}
template <typename T>
inline void read(T &s) {
  s = 0;
  int w = 1;
  char c = getchar();
  while (!isdigit(c)) {
    if (c == '-') w = -1;
    c = getchar();
  }
  while (isdigit(c)) s = (s * 10) + (c ^ 48), c = getchar();
  s = s * w;
}
template <typename T, typename... Args>
inline void read(T &x, Args &...args) {
  read(x), read(args...);
}
template <typename T>
inline void write(T x, char ch) {
  if (x < 0) x = -x, putchar('-');
  static char stk[25];
  int top = 0;
  do {
    stk[top++] = x % 10 + '0', x /= 10;
  } while (x);
  while (top) putchar(stk[--top]);
  if (ch != '~') putchar(ch);
  return;
}
}  // namespace FastIO
using namespace FastIO;

namespace MTool {
#define TA template <typename T, typename... Args>
#define TT template <typename T>
static const int Mod = 998244353;
TT inline void Swp(T &a, T &b) {
  T t = a;
  a = b;
  b = t;
}
TT inline void cmax(T &a, T b) { a = max(a, b); }
TT inline void cmin(T &a, T b) { a = min(a, b); }
TA inline void cmax(T &a, T b, Args... args) { a = max({a, b, args...}); }
TA inline void cmin(T &a, T b, Args... args) { a = min({a, b, args...}); }
TT inline void Madd(T &a, T b) { a = a + b >= Mod ? a + b - Mod : a + b; }
TT inline void Mdel(T &a, T b) { a = a - b < 0 ? a - b + Mod : a - b; }
TT inline void Mmul(T &a, T b) { a = a * b % Mod; }
TT inline void Mmod(T &a) { a = (a % Mod + Mod) % Mod; }
TT inline T Cadd(T a, T b) { return a + b >= Mod ? a + b - Mod : a + b; }
TT inline T Cdel(T a, T b) { return a - b < 0 ? a - b + Mod : a - b; }
TT inline T Cmul(T a, T b) { return a * b % Mod; }
TT inline T Cmod(T a) { return (a % Mod + Mod) % Mod; }
TA inline void Madd(T &a, T b, Args... args) { Madd(a, Cadd(b, args...)); }
TA inline void Mdel(T &a, T b, Args... args) { Mdel(a, Cadd(b, args...)); }
TA inline void Mmul(T &a, T b, Args... args) { Mmul(a, Cmul(b, args...)); }
TA inline T Cadd(T a, T b, Args... args) { return Cadd(Cadd(a, b), args...); }
TA inline T Cdel(T a, T b, Args... args) { return Cdel(Cdel(a, b), args...); }
TA inline T Cmul(T a, T b, Args... args) { return Cmul(Cmul(a, b), args...); }
TT inline T qpow(T a, T b) {
  int res = 1;
  while (b) {
    if (b & 1) Mmul(res, a);
    Mmul(a, a);
    b >>= 1;
  }
  return res;
}
TT inline T qmul(T a, T b) {
  int res = 0;
  while (b) {
    if (b & 1) Madd(res, a);
    Madd(a, a);
    b >>= 1;
  }
  return res;
}
TT inline T spow(T a, T b) {
  int res = 1;
  while (b) {
    if (b & 1) res = qmul(res, a);
    a = qmul(a, a);
    b >>= 1;
  }
  return res;
}
TT inline void exgcd(T A, T B, T &X, T &Y) {
  if (!B) return X = 1, Y = 0, void();
  exgcd(B, A % B, Y, X), Y -= X * (A / B);
}
TT inline T Ginv(T x) {
  T A = 0, B = 0;
  exgcd(x, Mod, A, B);
  return Cmod(A);
}
#undef TT
#undef TA
}  // namespace MTool
using namespace MTool;

inline void file() {
  freopen(".in", "r", stdin);
  freopen(".out", "w", stdout);
  return;
}

bool Mbe;

namespace LgxTpre {
static const int MAX = 510;
static const int inf = 2147483647;
static const int INF = 1e7;

int n, m, deg[MAX];
int id[MAX], odd[MAX], all[MAX];
int x, y, c, w, fl;

namespace MaxFlowMinCost {
struct edge {
  int nex, to, val, flow;
} e[MAX << 1];
int head[MAX], cnt = 1;
inline void add(int x, int y, int val, int flow) {
  e[++cnt].nex = head[x], head[x] = cnt, e[cnt].to = y, e[cnt].val = val,
  e[cnt].flow = flow;
  e[++cnt].nex = head[y], head[y] = cnt, e[cnt].to = x, e[cnt].val = -val,
  e[cnt].flow = 0;
  return;
}

int s, t;
int maxflow, mincost;
int dis[MAX], vis[MAX], pre[MAX], incf[MAX];
queue<int> q;
inline bool SPFA() {
  fill(vis + 1, vis + n + 1, 0), fill(dis + 1, dis + n + 1, INF);
  q.push(s), vis[s] = 1, dis[s] = 0, incf[s] = INF;
  while (!q.empty()) {
    int now = q.front();
    q.pop();
    vis[now] = 0;
    for (int i = head[now]; i; i = e[i].nex) {
      int to = e[i].to, val = e[i].val, flow = e[i].flow;
      if (!flow) continue;
      if (dis[to] > dis[now] + val) {
        dis[to] = dis[now] + val, incf[to] = min(incf[now], flow), pre[to] = i;
        if (!vis[to]) vis[to] = 1, q.push(to);
      }
    }
  }
  return dis[t] != INF;
}
inline void Augment() {
  int now = t;
  if (incf[t] * dis[t] > 0) return fl = 1, void();
  maxflow += incf[t], mincost += incf[t] * dis[t];
  while (now != s) {
    int i = pre[now];
    e[i].flow -= incf[t], e[i ^ 1].flow += incf[t], now = e[i ^ 1].to;
  }
}
inline void solve() {
  while (SPFA() && !fl) Augment();
}
}  // namespace MaxFlowMinCost
using namespace MaxFlowMinCost;

inline void mian() {
  read(n, m), s = 1, t = n;
  for (int i = 1; i <= m; ++i) {
    read(x, y, c, w);
    if (c & 1) odd[i] = 1, --deg[x], ++deg[y], --c;
    add(x, y, w, c >> 1), id[i] = cnt;
  }
  for (int i = 2; i < n; ++i) {
    if (deg[i] & 1) return puts("Impossible"), void();
    deg[i] >>= 1;
    if (!deg[i]) continue;
    if (deg[i] > 0)
      add(s, i, -INF, deg[i]);
    else
      add(i, t, -INF, -deg[i]);
  }
  MaxFlowMinCost::solve();
  for (int i = 1; i <= m; ++i)
    all[e[id[i]].to] += e[id[i]].flow << 1 | odd[i],
        all[e[id[i] ^ 1].to] -= e[id[i]].flow << 1 | odd[i];
  for (int i = 2; i < n; ++i)
    if (all[i]) return puts("Impossible"), void();
  puts("Possible");
  for (int i = 1; i <= m; ++i) write(e[id[i]].flow << 1 | odd[i], ' ');
  return puts(""), void();
}
}  // namespace LgxTpre

bool Med;

signed main() {
  //  file();
  fprintf(stderr, "%.3lf MB\n", abs(&Med - &Mbe) / 1048576.0);
  int Tbe = clock();
  LgxTpre::mian();
  int Ted = clock();
  cerr << 1e3 * (Ted - Tbe) / CLOCKS_PER_SEC << " ms\n";
  return (0 - 0);
}
