#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;
  std::vector adj(n + 1, std::vector<bool>(n + 1));
  std::vector<int> deg(n + 1);
  for (int i = 0; i < n; i++) {
    std::vector<int> a(n);
    for (int j = 0; j < n - 1; j++) {
      std::cin >> a[j];
      for (int k = 0; k < j; k++) {
        if (adj[a[k]][a[j]]) {
          continue;
        }
        adj[a[k]][a[j]] = true, deg[a[j]]++; 
      }
    }
  }

  std::queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (!deg[i]) {
      q.push(i), std::cout << i << " ";
    }
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 1; i <= n; i++) {
      if (!adj[u][i]) {
        continue;
      }
      if (!--deg[i]) {
        std::cout << i << " ";
        q.push(i);
      }
    }
  }
  std::cout << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}