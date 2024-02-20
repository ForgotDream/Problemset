#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2.5e5 + 5, INF = 1e9;

int n, m;
int h[N], to[N << 1], nxt[N << 1], val[N << 1], cnt;
void add(int u, int v, int w) {
  to[++cnt] = v, val[cnt] = w, nxt[cnt] = h[u], h[u] = cnt;
}
int minv[N];
int dep[N], dfn[N], tim;
int st[20][N];
int a[N];
int p[N];
bool key[N];

void dfs(int u, int fath) {
  dfn[u] = ++tim, dep[u] = dep[fath] + 1;
  st[0][dfn[u]] = fath;
  for (int i = h[u]; i; i = nxt[i]) {
    int v = to[i], w = val[i];
    if (v == fath) continue;
    minv[v] = min(minv[u], w);
    dfs(v, u);
  }
}

inline int calc(int u, int v) { return dfn[u] < dfn[v] ? u : v; }

void init() {
  for (int i = 1; i <= std::__lg(n); i++) {
    for (int j = 1; j <= n - (1 << i) + 1; j++) {
      st[i][j] = calc(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
}

inline int lca(int u, int v) {
  if (u == v) return u;
  u = dfn[u], v = dfn[v];
  if (u > v) std::swap(u, v);
  int d = std::__lg(v - u++);
  return calc(st[d][u], st[d][v - (1 << d) + 1]);
}

vector<int> e[N];

LL dp(int u) {
  LL ans = 0;
  for (auto v : e[u]) {
    if (key[v]) ans += minv[v];
    else ans += std::min(dp(v), 1ll * minv[v]);
  }
  return ans;
}

bool cmp(int u, int v) { return dfn[u] < dfn[v]; }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    add(u, v, w);
    add(v, u, w);
  }

  minv[1] = INF;
  dfs(1, 0), init();

  cin >> m;
  while (m--) {
    int c;
    cin >> c;
    int tot = 0;
    for (int i = 1; i <= c; i++) {
      cin >> p[i];
      a[++tot] = p[i];
      key[p[i]] = true;
    }
    a[++tot] = 1;
    sort(p + 1, p + 1 + c, cmp);
    for (int i = 1; i < c; i++) {
      a[++tot] = lca(p[i], p[i + 1]);
    }
    sort(a + 1, a + 1 + tot, cmp);
    tot = unique(a + 1, a + 1 + tot) - a - 1;
    for (int i = 1; i < tot; i++) {
      e[lca(a[i], a[i + 1])].push_back(a[i + 1]);
    }
    cout << dp(1) << '\n';
    for (int i = 1; i <= c; i++) {
      key[p[i]] = false;
    }
    for (int i = 1; i <= tot; i++) {
      e[a[i]].clear();
    }
  }

  return 0;
}
