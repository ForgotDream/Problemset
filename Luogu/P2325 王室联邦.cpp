/**
 * @file    P2325 王室联邦.cpp
 * @author  ForgotDream
 * @brief   树分块
 * @date    2023-06-03
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, b;
  std::cin >> n >> b;

  std::vector<std::vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int cnt = 0;
  std::vector<int> bln(n), cap;
  std::stack<int> s;
  std::function<void(int, int)> dfs = [&](int u, int frm) {
    int curSize = s.size();
    for (auto v : adj[u]) {
      if (v == frm) {
        continue;
      }
      dfs(v, u);
      if (s.size() >= curSize + b) {
        cap.push_back(u);
        cnt++;
        while (s.size() > curSize) {
          bln[s.top()] = cnt;
          s.pop();
        }
      }
    }
    s.push(u);
    if (u == 0) {
      while (!s.empty()) {
        bln[s.top()] = cnt;
        s.pop();
      }
    }
  };

  dfs(0, 0);

  std::cout << cnt << "\n";
  for (int i = 0; i < n; i++) {
    std::cout << bln[i] << " \n"[i == n - 1];
  }
  for (int i = 0; i < cnt; i++) {
    std::cout << cap[i] + 1 << " \n"[i == cnt - 1];
  }

  return 0;
}
