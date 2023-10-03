#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 1e5 + 50;
int n, m;
std::vector<pii> adj[N];
bool del[N];
int deg[N], cur[N], cnt;
std::vector<std::vector<int>> ans;
std::set<int> d;
void dfs(int u) {
  for (int &i = cur[u]; i < adj[u].size();) {
    auto [v, idx] = adj[u][i];
    if (!del[std::abs(idx)]) {
      del[std::abs(idx)] = true, cnt--, deg[u]--, deg[v]--;
      if (deg[u] == 1) d.insert(u);
      else if (deg[u] == 0) d.erase(u);
      if (deg[v] == 1) d.insert(v);
      else if (deg[v] == 0) d.erase(v);
      ans.back().push_back(idx);
      i++, dfs(v);
      break;
    } else {
      i++;
    }
  }
}
void solve() {
  std::cin >> n >> m;
  std::memset(del, 0, sizeof(del)), std::memset(cur, 0, sizeof(cur));
  std::memset(deg, 0, sizeof(deg)), ans.clear(), d.clear();
  for (int i = 1; i <= n; i++) adj[i].clear();
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].emplace_back(v, i), adj[v].emplace_back(u, -i);
    deg[u]++, deg[v]++;
  }
  for (int i = 1; i <= n; i++) {
    if (deg[i] == 1) d.insert(i);
  }
  cnt = m;
  while (cnt) {
    ans.push_back(std::vector<int>());
    if (ans.size() > 1) {
      for (int i = 1; i <= n; i++)
      break;
    }
    dfs(*d.begin());
  }
  int sum = 0;
  for (int i = 1; i <= n; i++) sum += deg[i];
  std::cout << ans.size() - 1 << "\n";
  for (const auto &i : ans) {
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
