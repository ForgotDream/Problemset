#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<std::vector<std::pair<int, int>>> adj(n);
  std::vector<int> used(n);
  std::queue<std::pair<int, int>> q;
  used[0] = 1;
  q.emplace(0, -1);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    adj[u].emplace_back(v, i);
    adj[v].emplace_back(u, i);
    if (used[u] && !used[v]) {
      used[v] = 1;
      q.emplace(v, i);
    } else if (used[v] && !used[u]) {
      used[u] = 1;
      q.emplace(u, i);
    }
  }

  while (!q.empty()) {
    auto cur = q.front();
    int u = cur.first, curId = cur.second;
    q.pop();
    for (auto i : adj[u]) {
      int v = i.first, id = i.second;
      if (!used[v]) {
        used[v] = used[u] + (id <= curId);
        q.emplace(v, id);
      }
    }
  }

  std::cout << *max_element(used.begin(), used.end()) << "\n";

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