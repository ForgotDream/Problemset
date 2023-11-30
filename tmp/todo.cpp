/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-11-28
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using pii = std::pair<int, int>;

constexpr int N = 1e6 + 50;
int n, m;
std::vector<int> bln[N];
std::set<int> cur[N], rst[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1, k, u; i <= m; i++) {
    std::cin >> k, rst[k].insert(i);
    while (k--) std::cin >> u, bln[u].push_back(i), cur[i].insert(u);
  }
  for (auto i : bln[1]) {
    rst[cur[i].size()].erase(i);
    cur[i].erase(1);
    rst[cur[i].size()].insert(i);
  }
  int ans = 1;
  while (true) {
    std::vector<int> p;
    for (auto i : rst[1]) {
      int u = *cur[i].begin();
      ans++, p.push_back(u);
    }
    for (auto i : p) {
      for (auto j : bln[i]) {
        rst[cur[j].size()].erase(j);
        cur[j].erase(i);
        rst[cur[j].size()].insert(j);
      }
    }
    if (rst[1].empty()) break;
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
