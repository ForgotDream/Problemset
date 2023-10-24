/**
 * @file    CF274D Lovely Matrix.cpp
 * @author  ForgotDream
 * @brief   Topo Sort
 * @date    2023-09-04
 */
#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 5;
int n, m, tot;
int deg[N << 1];
std::vector<int> adj[N << 1];
void solve() {
  std::cin >> n >> m;
  std::vector val(n + 1, (std::vector<int>(m + 1)));
  tot = m;
  for (int i = 1; i <= n; i++) {
    std::vector<int> b;
    for (int j = 1; j <= m; j++) {
      std::cin >> val[i][j];
      if (~val[i][j]) b.push_back(val[i][j]);
    }
    std::sort(b.begin(), b.end());
    b.erase(std::unique(b.begin(), b.end()), b.end());
    for (int j = 1; j <= m; j++) {
      if (~val[i][j])
        val[i][j] = std::lower_bound(b.begin(), b.end(), val[i][j]) -
                    b.begin() + 1;
    }
    for (int j = 2; j <= b.size(); j++) {
      adj[tot + j].push_back(tot + j - 1);
      deg[tot + j - 1]++;
    }
    for (int j = 1; j <= m; j++)
      if (~val[i][j]) {
        adj[j].push_back(tot + val[i][j]);
        deg[tot + val[i][j]]++;
        if (val[i][j] != b.size()) {
          adj[tot + val[i][j] + 1].push_back(j);
          deg[j]++;
        }
      }
    tot += b.size();
  }
  std::vector<int> ans;
  std::queue<int> q;
  for (int i = 1; i <= tot; i++) {
    if (!deg[i]) q.push(i);
  }
  int cnt = 0;
  while (!q.empty()) {
    auto pos = q.front();
    q.pop();
    ans.push_back(pos);
    cnt += (pos <= m);
    for (auto Next : adj[pos])
      if (!--deg[Next]) q.push(Next);
  }
  if (cnt == m) {
    std::reverse(ans.begin(), ans.end());
    for (auto x : ans) {
      if (x <= m) std::cout << x << " ";
    }
    std::cout << "\n";
  } else {
    std::cout << -1 << "\n";
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}