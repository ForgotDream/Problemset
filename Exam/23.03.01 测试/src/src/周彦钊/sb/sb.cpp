#include <bits/stdc++.h>

using i64 = long long;

static const int INF = 0x3f3f3f3f;

template<int N>
struct Tree {
  int n;
  std::vector<int> e[N], f[2], dis, ans, nxt;
  std::vector<bool> vis;
  int L, R, D;
  
  Tree(int num) {
    f[0].resize(N, 0);
    f[1].resize(N, 0);
    dis.resize(N, 0);
    ans.resize(N, 0);
    nxt.resize(N, 0);
    vis.resize(N, 0);
    n = num;
    L = 0, R = 0, D = 0;
    return;
  }
  
  void add(int u, int v) {
    e[u].push_back(v);
    return;
  }
  
  void dfs(int u, int from) {
    dis[u] = dis[from] + 1;
    nxt[u] = from;
    for (auto v : e[u]) {
      if (v == from) {
        continue;
      }
      dfs(v, u);
    }
    return;
  }
  
  void get() {
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
      if (dis[L] < dis[i]) {
        L = i;
      }
    }
    dfs(L, 0);
    for (int i = 1; i <= n; i++) {
      if (dis[R] < dis[i]) {
        R = i;
      }
    }
    D = dis[R] - dis[L];
    return;
  }
  
  void dfs2(int u, int from, int pivot) {
    for (auto v : e[u]) {
      if (v == from || vis[v]) {
        continue;
      }
      dis[v] = dis[u] + 1;
      ans[v] = dis[v] + ans[pivot];
      dfs2(v, u, pivot);
    }
    return;
  }
  
  void solve() {
    int pivot = 0;
    for (int i = R; i; i = nxt[i]) {
      ans[i] = std::max(D - pivot, pivot);
      dis[i] = 0;
      vis[i] = true;
      pivot++;
    }
    for (int i = R; i; i = nxt[i]) {
      dfs2(i, 0, i);
    }
    for (int i = 1; i <= n; i++) {
      std::cout << ans[i] << "\n";
    }
    return;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  int n;
  std::cin >> n;
  Tree<10050> G(n);
  for (int i = 1; i < n; i++) {
    int u, v;
    std::cin >> u >> v;
    G.add(u, v);
    G.add(v, u);
  }
  
  G.get();
  G.solve();
  
  return 0;
}
