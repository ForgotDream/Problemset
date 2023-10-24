/**
 * @file    AT_joisc2020_e ジョイッターで友だちをつくろう.cpp
 * @author  ForgotDream
 * @brief   DSU
 * @date    2023-07-27
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m;
std::set<int> out[N], in[N], edgeCnt[N], reachin[N];
std::queue<std::pair<int, int>> q;
i64 ans, tmp;

i64 calc(int u) {
  i64 siz = edgeCnt[u].size();
  return siz * (siz - 1 + (i64)reachin[u].size());
}

struct DSU {
  int fa[N];
  DSU() { std::iota(fa, fa + N, 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    tmp -= calc(u) + calc(v);
    if (edgeCnt[u].size() < edgeCnt[v].size()) std::swap(u, v);
    fa[v] = u;
    for (auto i : edgeCnt[v]) edgeCnt[u].insert(i), reachin[u].erase(i);
    for (auto i : reachin[v]) if (!edgeCnt[u].count(i)) reachin[u].insert(i);
    for (auto i : in[v]) {
      if (i != u) out[i].erase(v), out[i].insert(u);
      if (!edgeCnt[u].count(i)) {
        in[u].insert(i);
        if (out[u].count(i)) q.emplace(u, i);
      }
    }
    for (auto i : out[v]) {
      if (i != u) in[i].erase(v), in[i].insert(u);
      if (!edgeCnt[u].count(i)) {
        out[u].insert(i);
        if (in[u].count(i)) q.emplace(u, i);
      }
    }
    in[v].clear(), out[v].clear(), edgeCnt[v].clear(), reachin[v].clear();
    tmp += calc(u);
    return true;
  }
} dsu;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) edgeCnt[i].insert(i);
  while (m--) {
    int u, v;
    std::cin >> u >> v;
    int fau = dsu.find(u), fav = dsu.find(v);
    if (fau == fav) {
      std::cout << ans << "\n";
      continue;
    }
    if (in[fau].count(fav)) {
      dsu.merge(u, v);
      while (!q.empty()) {
        auto [tu, tv] = q.front();
        q.pop();
        dsu.merge(tu, tv);
      }
    } else if (!reachin[fav].count(u)) {
      reachin[fav].insert(u);
      out[fau].insert(fav);
      in[fav].insert(fau);
      tmp += edgeCnt[fav].size();
    }
    std::cout << (ans = std::max(ans, tmp)) << "\n";
  }

  return 0;
}