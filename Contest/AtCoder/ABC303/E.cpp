#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<std::vector<int>> adj(n);
  std::vector<int> deg(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
    deg[u]++, deg[v]++;
  }

  std::vector<int> bln(n, -1);
  std::function<void(int, int)> dfs = [&](int u, int frm) {
    bool flg = false;
    for (int v : adj[u]) {
      if (v == frm) {
        continue;
      }
      flg = true;
      dfs(v, u);
      if (bln[v] == v) {
        bln[u] = v;
      } else if (bln[v] == u) {
        bln[u] = u;
      } else {
        bln[u] = frm;
      }
    }
    if (!flg) {
      bln[u] = frm;
    }
  };

  dfs(0, 0);

  std::vector<int> siz(n);
  for (int i = 0; i < n; i++) {
    // std::cerr << bln[i] << " \n"[i == n - 1];
    siz[bln[i]]++;
  }

  std::multiset<int> s;
  for (int i = 0; i < n; i++) {
    if (siz[i]) {
      s.insert(siz[i] - 1);
    }
  }

  for (auto it : s) {
    std::cout << it << " ";
  }
  std::cout << "\n";

  return 0;
}