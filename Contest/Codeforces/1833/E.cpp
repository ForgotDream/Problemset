#include <bits/stdc++.h>

using i64 = long long;

struct DSU {
  int n;
  std::vector<int> fa;

  DSU(int _n) {
    n = _n;
    fa.resize(n);
    std::iota(fa.begin(), fa.end(), 0);
  }

  int find(int u) {
    while (u != fa[u]) { u = fa[u] = fa[fa[u]]; }
    return u;
  }

  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) {
      return false;
    }
    fa[u] = v;
    return true;
  }
};

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  DSU dsu(n);
  int cir = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    a[i]--;
    if (!dsu.merge(i, a[i])) {
      // cir++;
    }
  }

  std::vector<bool> det(n);
  for (int i = 0; i < n; i++) {
    if (i != a[a[i]]) {
      det[a[i]] = true;
    }
  }

  std::vector<bool> used(n);
  for (int i = 0; i < n; i++) {
    if (!det[i]) {
      used[dsu.find(i)] = true;
    }
  }

  cir = std::count(used.begin(), used.end(), true);

  int cnt = 0;
  for (int i = 0; i < n; i++) {
    if (dsu.find(i) == i) {
      cnt++;
    }
  }

  std::cout << std::min(cnt, cnt - cir + 1) << " " << cnt << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}