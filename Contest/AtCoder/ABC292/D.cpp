#include <bits/stdc++.h>

using i64 = long long;

struct Graph {
  int n, m;
  std::vector<std::vector<std::pair<int, int>>> e;
  std::vector<bool> vis, ver;
  int cnt, edgeCnt;
  std::vector<int> edgeNum;
  std::vector<std::set<int>> verNum;

  Graph(const int &n, const int &m) : n(n), m(m) {
    e.resize(n + 1);
    vis.resize(m + 1);
    edgeNum.resize(n + 1);
    verNum.resize(n + 1);
    ver.resize(n + 1);
    cnt = edgeCnt = 0;
    return;
  }

  void add(int u, int v) {
    e[u].emplace_back(v, ++edgeCnt);
    e[v].emplace_back(u, edgeCnt);
    return;
  }

  bool init() {
    for (int u = 1; u <= n; u++) {
      int diff = 0;
      for (auto i : e[u]) {
        int v = i.first;
        if (u == v) {
          diff++;
        }
      }
      // std::cerr << u << " " << 
      if (diff > 2) {
        return false;
      }
    }
    return true;
  }

  void dfs(int u) {
    ver[u] = true;
    verNum[cnt].insert(u);
    for (auto i : e[u]) {
      int v = i.first, no = i.second;
      // std::cerr << u << " " << v << "\n";
      if (vis[no]) {
        continue;
      }
      vis[no] = true;
      edgeNum[cnt]++;
      dfs(v);
    }
    return;
  }

  void solve() {
    if (!init()) {
      std::cout << "No" << "\n";
      return;
    }
    for (int i = 1; i <= n; i++) {
      if (!ver[i]) {
        // std::cerr << i << " " << ver[i] << "\n";
        cnt++;
        // std::cerr << cnt << "\n";
        dfs(i);
      }
    }
    for (int i = 1; i <= cnt; i++) {
      if (edgeNum[i] != verNum[i].size()) {
        std::cout << "No" << "\n";
        return;
      }
      // std::cerr << edgeNum[i] << " " << verNum[i].size() << "\n";
      // for (auto j : verNum[i]) {
      //   std::cerr << j << "\n";
      // }
    }
    std::cout << "Yes" << "\n";
    return;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  Graph G(n, m);
  for (int i = 1; i <= m; i++) {
    int u, v;
    std::cin >> u >> v;
    G.add(u, v);
  }

  G.solve();

  return 0;
}