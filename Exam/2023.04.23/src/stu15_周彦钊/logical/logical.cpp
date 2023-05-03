#include <bits/stdc++.h>

using i64 = long long;

namespace myFile {
void useFileIO() {
  freopen("logical.in", "r", stdin);
  freopen("logical.out", "w", stdout);
  return;
}
}

struct Tree {
  int n;
  std::vector<std::vector<int>> ch;
  std::vector<int> type, f, pre;
  
  Tree(int n) : n(n + 1) {
    ch.resize(n + 1);
    type.resize(n + 1, 0);
    f.resize(n + 1, 0);
    pre.resize(n + 1, 0);
    return;
  }
  
  bool add(int u, int lc, int rc) {
    ch[u].resize(2);
    ch[u][0] = lc, ch[u][1] = rc;
    return true;
  }
  
  void dfs(int u) {
    if (ch[u].empty()) {
      return;
    }
    int lc = ch[u][0], rc = ch[u][1];
    dfs(lc), dfs(rc);
    if (type[u] == 1) {
      pre[u] = pre[lc] & pre[rc];
    } else if (type[u] == 2) {
      pre[u] = pre[lc] | pre[rc];
    } else {
      pre[u] = pre[lc] ^ pre[rc];
    }
    return;
  }
  
  void solve(int u) {
    if (ch[u].empty()) {
      f[u] = 1;
      return;
    } 
    int lc = ch[u][0], rc = ch[u][1];
    solve(lc), solve(rc);
    if (type[u] == 1) {
      if (pre[u]) {
        f[u] = std::min(f[lc], f[rc]);
      } else {
        f[u] = (!pre[lc]) * f[lc] + (!pre[rc]) * f[rc];
      }
    } else if (type[u] == 2) {
      if (pre[u]) {
        f[u] = pre[lc] * f[lc] + pre[rc] * f[rc];
      } else {
        f[u] = std::min(f[lc], f[rc]);
      }
    } else {
      f[u] = std::min(f[lc], f[rc]);
    }
    return;
  }
};

int main() {
  // myFile::useFileIO();
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  int n, m;
  std::cin >> n >> m;
  
  Tree tree(n);
  int root = 1;
  for (int i = 0; i < n; i++) {
    int x, y, z, a;
    std::cin >> x >> y >> z >> a;
    if (!z) {
      root = i + 1;
    }
    x == 0 || tree.add(i + 1, x, y);
    tree.type[i + 1] = a;
  }
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    tree.pre[x] = y;
  }
  
  tree.dfs(root), tree.solve(root);
  std::cout << tree.f[root] << "\n";
  
  return 0;
}
