/*
 * @file    P5632 【模板】Stoer-Wagner.cpp
 * @author  ForgotDream
 * @brief   Stoer Wagner
 * @date    2024-01-23
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 605, inf = 0x3f3f3f3f;

int n, m;
int adj[N][N];

int fa[N], siz[N];
inline int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }

int dis[N];
bool vis[N], del[N];

int constract(int &s, int &t) {
  memset(dis, 0, sizeof(dis)), dis[0] = -1;
  memset(vis, false, sizeof(vis));
  int res = inf;
  for (int i = 1; i <= n; i++) {
    int p = 0;
    for (int j = 1; j <= n; j++) {
      if (!del[j] && !vis[j] && dis[j] > dis[p]) p = j;
    }
    if (p == 0) return res;
    s = t, t = p, res = dis[p], vis[p] = true;
    for (int j = 1; j <= n; j++) {
      if (!del[j] && !vis[j]) dis[j] += adj[p][j];
    }
  }
  return res;
}

int calc() {
  int s, t, res = inf;
  for (int i = 1; i < n; i++) {
    int cur = constract(s, t);
    del[t] = true, res = std::min(res, cur);
    if (!res) return 0;
    for (int j = 1; j <= n; j++) {
      if (!del[j]) adj[s][j] = (adj[j][s] += adj[j][t]);
    }
  }
  return res;
}

void solve() {
  std::cin >> n >> m;
  std::iota(fa + 1, fa + n + 1, 1);
  std::fill(siz + 1, siz + n + 1, 1);

  for (int i = 1, u, v, w; i <= m; i++) {
    std::cin >> u >> v >> w;
    adj[u][v] += w, adj[v][u] += w;

    int fu = find(u), fv = find(v);
    if (fu != fv) {
      if (siz[fu] > siz[fv]) std::swap(fu, fv);
      siz[fv] += siz[fu], fa[fu] = fv;
    }
  }

  if (siz[find(1)] != n) {
    std::cout << 0 << "\n";
    return;
  }

  std::cout << calc() << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
