/**
 * @file    CF980D Perfect Groups.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-27
 */
#include <bits/stdc++.h>

using i64 = long long;

struct DSU {
  int n;
  std::vector<int> fa;
  DSU(int _n = 0) {
    n = _n;
    fa.resize(n);
    std::iota(fa.begin(), fa.end(), 0);
  }
  int find(int u) {
    while (u != fa[u]) {
      u = fa[u] = fa[fa[u]];
    }
    return u;
  }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u != v) {
      fa[u] = v;
    }
    return u != v;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  DSU dsu(n);
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (1ll * a[i] * a[j] > 0) {
        int sqr = std::sqrt(1ll * a[i] * a[j]);
        if (1ll * sqr * sqr == 1ll * a[i] * a[j]) {
          dsu.merge(i, j);
        }
      }
    }
  }

  std::vector<int> ans(n + 1);
  for (int i = 0; i < n; i++) {
    int cnt = 0;
    std::vector<bool> bln(n);
    for (int j = i; j < n; j++) {
      if (!a[j]) {
        ans[std::max(1, cnt)]++;
      } else {
        if (!bln[dsu.find(j)]) {
          bln[dsu.find(j)] = true;
          ++cnt;
        }
        ans[cnt]++;
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    std::cout << ans[i] << " \n"[i == n];
  }

  return 0;
}
