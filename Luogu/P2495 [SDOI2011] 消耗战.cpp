/*
 * @file    P2495 [SDOI2011] 消耗战.cpp
 * @author  ForgotDream
 * @brief   Virtual Tree
 * @date    2023-12-25
 */
#include <bits/stdc++.h>

using i64 = long long;
using pil = std::pair<int, i64>;

constexpr int N = 3e5 + 50;
int n, m;
std::vector<pil> adj[N];

int st[20][N], dfn[N], clk;
i64 dis[N];
void dfs(int u, int frm) {
  st[0][dfn[u] = ++clk] = frm;
  for (auto [v, w] : adj[u]) {
    if (v == frm) continue;
    dis[v] = std::min(dis[u], w), dfs(v, u);
  }
}
inline int cmp(int u, int v) { return dfn[u] < dfn[v] ? u : v; }
void init() {
  for (int i = 1; i <= std::__lg(n); i++) {
    for (int j = 1; j <= n - (1 << i) + 1; j++) {
      st[i][j] = cmp(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
}
inline int get_lca(int u, int v) {
  if (u == v) return u;
  u = dfn[u], v = dfn[v];
  if (u > v) std::swap(u, v);
  int d = std::__lg(v - u++);
  return cmp(st[d][u], st[d][v - (1 << d) + 1]);
}

int k, a[N];
bool tag[N];
i64 f[N];

std::vector<pil> vadj[N];
int stk[N], top;
inline void add(int u, int v) {
  vadj[u].emplace_back(v, dis[v]);
}
void build() {
  std::sort(a + 1, a + k + 1, [&](int lhs, int rhs) {
    return dfn[lhs] < dfn[rhs];
  });

  stk[top = 1] = 1, vadj[1].clear();
  for (int i = 1; i <= k; i++) {
    if (a[i] == 1) continue;

    int lca = get_lca(stk[top], a[i]);
    if (lca != stk[top]) {
      while (dfn[lca] < dfn[stk[top - 1]]) {
        add(stk[top - 1], stk[top]), top--;
      }

      if (dfn[lca] > dfn[stk[top - 1]]) {
        vadj[lca].clear(), add(lca, stk[top]);
        stk[top] = lca;
      } else {
        add(lca, stk[top--]);
      }
    }
    vadj[a[i]].clear(), stk[++top] = a[i];
  }
  for (int i = 1; i < top; i++) {
    add(stk[i], stk[i + 1]);
  }
}

void dp(int u) {
  f[u] = 0;
  for (auto [v, w] : vadj[u]) {
    dp(v);
    if (tag[v]) f[u] = f[u] + w;
    else f[u] = f[u] + std::min(w, f[v]);
  }
}

void solve() {
  std::cin >> n;
  for (int i = 1, u, v, w; i < n; i++) {
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
  }

  dis[1] = 1e18;
  dfs(1, 0), init();

  std::cin >> m;
  while (m--) {
    std::cin >> k;
    for (int i = 1; i <= k; i++) std::cin >> a[i], tag[a[i]] = true;

    build(), dp(1);
    // std::cerr << "\n";
    std::cout << f[1] << "\n";

    for (int i = 1; i <= k; i++) tag[a[i]] = false;
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
