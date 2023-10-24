/**
 * @file    CF243B Hydra.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-08-16
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e5 + 50;
std::random_device rd;
std::mt19937 rng(rd());
int n, m, h, t, deg[N], p[N];
std::vector<int> adj[N];
void solve(int u, int v) {
  if (deg[u] < h || deg[v] < t) return;
  std::set<int> H, T, rst;
  for (auto i : adj[u]) {
    if (i != v) H.insert(i);
  }
  for (auto i : adj[v]) {
    if (i == u) continue;
    if (H.count(i)) H.erase(i), rst.insert(i);
    else T.insert(i);
  }
  if ((H.size() >= h && T.size() >= t) ||
      (!(H.size() >= h && T.size() + rst.size() < t) &&
       !(H.size() + rst.size() < h && T.size() >= t) &&
       !(H.size() + T.size() + rst.size() < h + t))) {
    std::cout << "YES\n";
    std::cout << u << " " << v << "\n";
    int p = 1;
    auto rit = rst.begin();
    for (auto it = H.begin(); p <= h && it != H.end(); p++, it++) {
      std::cout << *it << " \n"[p == h];
    }
    if (p <= h) {
      for (; p <= h; p++, rit++) std::cout << *rit << " \n"[p == h];
    }
    // std::cerr << "OK\n";
    p = 1;
    for (auto it = T.begin(); p <= t && it != T.end(); p++, it++) {
      std::cout << *it << " \n"[p == t];
    }
    if (p <= t) {
      for (; p <= t; p++, rit++) std::cout << *rit << " \n"[p == t];
    }
    exit(0);
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m >> h >> t;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
    deg[u]++, deg[v]++;
  }
  for (int i = 1; i <= n; i++) deg[i]--;
  std::iota(p + 1, p + n + 1, 1);
  std::shuffle(p + 1, p + n + 1, rng);
  for (int u = 1; u <= n; u++) {
    std::shuffle(adj[p[u]].begin(), adj[p[u]].end(), rng);
    for (auto v : adj[p[u]]) solve(p[u], v);
  }
  std::cout << "NO\n";
  return 0;
}