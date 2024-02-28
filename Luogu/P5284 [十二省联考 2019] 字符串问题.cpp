/*
 * @file    P5284 [十二省联考 2019] 字符串问题.cpp
 * @author  ForgotDream
 * @brief   SAM + Topo Sort
 * @date    2024-02-23
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using pii = std::pair<int, int>;

constexpr int N = 4e5 + 50;

int n, na, nb, m;
char s[N];
int la[N], ra[N], lb[N], rb[N];

struct SAM {
  int ch[N][26], len[N], link[N], lst = 1, cnt = 1;

  void clear() {
    memset(ch + 1, 0, sizeof(int[26]) * cnt);
    memset(len + 1, 0, sizeof(int) * cnt);
    memset(link + 1, 0, sizeof(int) * cnt);
    lst = cnt = 1;
  }
  
  int expand(int d) {
    int cur = ++cnt;
    len[cur] = len[lst] + 1;
    int p = lst;
    for (; p && !ch[p][d]; p = link[p]) ch[p][d] = cur;
    if (!p) {
      link[cur] = 1;
    } else {
      int q = ch[p][d];
      if (len[p] + 1 == len[q]) {
        link[cur] = q;
      } else {
        int tmp = ++cnt;
        len[tmp] = len[p] + 1, link[tmp] = link[q];
        memcpy(ch[tmp], ch[q], sizeof(ch[tmp]));
        for (; p && ch[p][d] == q; p = link[p]) ch[p][d] = tmp;
        link[cur] = link[q] = tmp;
      }
    }
    return lst = cur;
  }
} sam;

int pos[N], deg[N];
std::vector<int> adj[N], g[N];
std::vector<pii> bln[N];

int fa[20][N];

bool vis[N];
i64 dis[N];

void init(int u) {
  for (int i = 1; i <= std::__lg(sam.cnt); i++) {
    fa[i][u] = fa[i - 1][fa[i - 1][u]];
  }
  for (auto v : adj[u]) fa[0][v] = u, init(v);
}

inline int find(int l, int r) {
  int u = pos[l], len = r - l + 1;
  for (int i = std::__lg(sam.cnt); ~i; i--) {
    if (sam.len[fa[i][u]] >= len) u = fa[i][u];
  }
  return u;
}

void clear() {
  for (int i = 1; i <= sam.cnt; i++) adj[i].clear(), bln[i].clear();
  for (int i = 0; i <= std::__lg(sam.cnt); i++) {
    memset(fa[i] + 1, 0, sizeof(int) * sam.cnt);
  }
  sam.clear();
  for (int i = 1; i <= na + nb; i++) g[i].clear();
  memset(dis + 1, 0, sizeof(i64) * (na + nb));
  memset(deg + 1, 0, sizeof(int) * (na + nb));
}

inline void add_edge(int u, int v) { g[u].push_back(v), deg[v]++; }

void build(int u, int pre = 0) {
  std::stable_sort(bln[u].begin(), bln[u].end());
  for (auto [_, v] : bln[u]) {
    v = -v;
    if (pre) add_edge(pre, v);
    if (v > na) pre = v;
  }
  for (auto v : adj[u]) build(v, pre);
}

inline int get_len(int u) {
  if (u > na) return 0;
  else return ra[u] - la[u] + 1;
}

void solve() {
  clear();

  std::cin >> (s + 1), n = strlen(s + 1);
  for (int i = n; i; i--) pos[i] = sam.expand(s[i] - 'a');

  for (int i = 2; i <= sam.cnt; i++) adj[sam.link[i]].push_back(i);
  init(1);

  std::cin >> na;
  for (int i = 1, p; i <= na; i++) {
    std::cin >> la[i] >> ra[i], p = find(la[i], ra[i]);
    bln[p].emplace_back(ra[i] - la[i] + 1, -i);
  }
  std::cin >> nb;
  for (int i = 1, p; i <= nb; i++) {
    std::cin >> lb[i] >> rb[i], p = find(lb[i], rb[i]);
    bln[p].emplace_back(rb[i] - lb[i] + 1, -(i + na));
  }
  build(1);

  std::cin >> m;
  for (int i = 1, u, v; i <= m; i++) std::cin >> u >> v, add_edge(u, v + na);

  std::queue<int> q;
  for (int i = 1; i <= na + nb; i++) if (!deg[i]) q.push(i), dis[i] = get_len(i);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : g[u]) {
      dis[v] = std::max(dis[v], dis[u] + get_len(v));
      if (!--deg[v]) q.push(v);
    }
  }

  i64 ans = 0;
  for (int i = 1; i <= na + nb; i++) {
    if (deg[i]) {
      std::cout << -1 << "\n";
      return;
    }
    ans = std::max(ans, dis[i]);
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
