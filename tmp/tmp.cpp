/**
 * @file
 * @author  ForgotDream
 * @brief
 * @date    2023-10-02
 */
#include <cstring>
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 1e5 + 50;
int n, m;
std::vector<pii> adj[N]; 
int deg[N], cur[N];
bool del[2 * N];
std::vector<std::vector<int>> ans;
bool vis[N];
void dfs(int u) {
  vis[u] = true;
  for (int &i = cur[u]; i < adj[u].size();) {
    auto [v, idx] = adj[u][i];
    if (!del[std::abs(idx)]) {
      del[std::abs(idx)] = true;
      i++, dfs(v);
      if (std::abs(idx) <= m) ans.back().push_back(-idx);
      else ans.push_back(std::vector<int>());
    } else {
      i++;
    }
  }
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) adj[i].clear();
  std::memset(deg, 0, sizeof(deg));
  std::memset(del, 0, sizeof(del));
  std::memset(cur, 0, sizeof(cur));
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].emplace_back(v, i), adj[v].emplace_back(u, -i);
    deg[u]++, deg[v]++;
  }
  int pre = 0, cnt = m;
  for (int i = 1; i <= n; i++) {
    if (!(deg[i] & 1)) continue;
    if (pre) {
      adj[pre].emplace_back(i, ++cnt), adj[i].emplace_back(pre, -cnt);
      pre = 0;
    } else {
      pre = i;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i] && (deg[i] & 1)) {
      ans.push_back(std::vector<int>());
      dfs(i);
      ans.pop_back();
    }
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i] && deg[i]) {
      ans.push_back(std::vector<int>());
      dfs(i);
    }
  }
  std::cout << ans.size() - 1 << "\n";
  for (auto &i : ans) {
    std::cout << i.size() << " ";
    for (auto j : i) std::cout << j << " ";
    std::cout << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
