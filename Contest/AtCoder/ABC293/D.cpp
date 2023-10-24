#include <bits/stdc++.h>

using i64 = long long;

struct DSU {
  int n;
  std::vector<int> fa;

  DSU(int n) {
    this->n = n;
    fa.resize(n);
    std::iota(fa.begin(), fa.end(), 0);
    return;
  }

  int find(int u) {
    return u == fa[u] ? u : fa[u] = find(fa[u]);
  }

  int merge(int u, int v) {
    int fau = find(u), fav = find(v);
    if (fau == fav) {
      return 1;
    }
    fa[fau] = fav;
    return 0;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m;
  std::cin >> n >> m;

  DSU dsu(2 * n + 50);
  for (int i = 1; i <= n; i++) {
    dsu.merge(i, i + n);
  }

  int ans = 0;
  for (int i = 1; i <= m; i++) {
    int u, v;
    char a, b;
    std::cin >> u >> a >> v >> b;
    ans += dsu.merge(u + (a == 'B') * n, v + (b == 'B') * n);
  }

  std::bitset<(int) 4e5 + 50> b;
  for (int i = 1; i <= 2 * n; i++) {
    b[dsu.find(i)] = true;
  }

  std::cout << ans << " " << b.count() - ans << "\n";

  return 0;
}