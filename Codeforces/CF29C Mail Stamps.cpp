/**
 * @file    CF29C Mail Stamps.cpp
 * @author  ForgotDream
 * @brief   树的直径
 * @date    2023-08-23
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n;
std::map<int, int> enc;
int dec[N], cnt;
std::vector<int> adj[N];
int dep[N], nxt[N];
void dfs(int u, int frm) {
  dep[u] = dep[frm] + 1, nxt[u] = frm;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
  }
}
void solve() {
  std::cin >> n;
  for (int i = 1, u, v; i <= n; i++) {
    std::cin >> u >> v;
    if (!enc.count(u)) enc[u] = ++cnt, dec[cnt] = u;
    if (!enc.count(v)) enc[v] = ++cnt, dec[cnt] = v;
    adj[enc[u]].push_back(enc[v]);
    adj[enc[v]].push_back(enc[u]);
  }
  dfs(1, 0);
  int l = std::max_element(dep + 1, dep + cnt + 1) - dep;
  dfs(l, 0);
  int r = std::max_element(dep + 1, dep + cnt + 1) - dep;
  // std::cerr << dec[l] << " " << dec[r] << "\n";
  while (r) std::cout << dec[r] << " ", r = nxt[r];
  std::cout << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}