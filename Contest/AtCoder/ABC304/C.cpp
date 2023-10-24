#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, d;
  std::cin >> n >> d;

  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].first >> a[i].second;
  }

  auto dis = [&](std::pair<int, int> lhs, std::pair<int, int> rhs) {
    return std::hypot(lhs.first - rhs.first, lhs.second - rhs.second);
  };

  std::queue<int> q;
  q.push(0);
  std::vector<bool> vis(n);
  vis[0] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < n; i++) {
      if (vis[i] || dis(a[u], a[i]) > d) {
        continue;
      }
      vis[i] = true;
      q.push(i);
    }
  }

  for (int i = 0; i < n; i++) {
    if (vis[i]) {
      std::cout << "Yes\n";
    } else {
      std::cout << "No\n";
    }
  }

  return 0;
}