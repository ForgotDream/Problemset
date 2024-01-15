/*
 * @file    P3346 [ZJOI2015] 诸神眷顾的幻想乡.cpp
 * @author  ForgotDream
 * @brief   GSAM
 * @date    2024-01-14
 */
#include <bits/stdc++.h>

using i64 = long long;

// 增量构造吧，直接拉出来不是很好写

constexpr int N = 4e6 + 50;

int n, c, a[N];
std::vector<int> adj[N];
int deg[N];

struct GSAM {
  int ch[N][10], link[N], len[N], cnt = 1;
  int expand(int lst, int d) {
    int cur = ch[lst][d];
    if (len[cur]) return cur;
    len[cur] = len[lst] + 1;
    int p = link[lst];
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
        for (int i = 0; i < c; i++) ch[tmp][i] = len[ch[q][i]] ? ch[q][i] : 0;
        for (; p && ch[p][d] == q; p = link[p]) ch[p][d] = tmp;
        link[cur] = link[q] = tmp;
      }
    }
    return cur;
  }
  void build() {
    std::queue<std::pair<int, int>> q;
    for (int i = 0; i < c; i++) if (ch[1][i]) q.emplace(1, i);
    while (!q.empty()) {
      auto [u, d] = q.front();
      q.pop(), u = expand(u, d);
      for (int i = 0; i < c; i++) if (ch[u][i]) q.emplace(u, i);
    }
  }
} gsam;

void dfs(int u, int frm, int p) {
  if (!gsam.ch[p][a[u]]) gsam.ch[p][a[u]] = ++gsam.cnt;
  p = gsam.ch[p][a[u]];
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u, p);
  }
}

void solve() {
  std::cin >> n >> c;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
    deg[u]++, deg[v]++;
  }

  for (int i = 1; i <= n; i++) if (deg[i] == 1) dfs(i, 0, 1);
  gsam.build();

  i64 ans = 0;
  for (int i = 1; i <= gsam.cnt; i++) ans += gsam.len[i] - gsam.len[gsam.link[i]];
  std::cout << ans << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
