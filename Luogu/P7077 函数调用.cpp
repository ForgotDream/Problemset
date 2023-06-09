/**
 * @file    P7077 函数调用.cpp
 * @author  ForgotDream
 * @brief   DP + Topo Sort
 * @date    2023-06-08
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

constexpr int mod = 998244353;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) { std::cin >> a[i]; }

  int m;
  std::cin >> m;
  std::vector<int> type(m), pos(m), val(m), deg(m);
  std::vector<std::vector<int>> link(m);
  for (int i = 0; i < m; i++) {
    std::cin >> type[i];
    if (type[i] == 1) {
      std::cin >> pos[i] >> val[i];
      pos[i]--;
    } else if (type[i] == 2) {
      std::cin >> val[i];
    } else {
      int c;
      std::cin >> c;
      link[i].resize(c);
      for (auto &j : link[i]) { std::cin >> j, deg[--j]++; }
    }
  }

  std::vector<i64> mul(m);
  std::vector<bool> used(m);
  std::function<void(int)> run = [&](int u) {
    used[u] = true, mul[u] = (type[u] == 2 ? val[u] : 1);
    for (auto v : link[u]) {
      if (!used[v]) { run(v); }
      (mul[u] *= mul[v]) %= mod;
    }
  };
  for (int i = 0; i < m; i++) {
    if (!used[i] && !deg[i]) { run(i); }
  }

  int q;
  std::cin >> q;
  std::vector<int> arr(q);
  for (int i = 0; i < q; i++) { std::cin >> arr[i], arr[i]--; }

  std::vector<i64> f(m);
  i64 cur = 1;
  for (int i = q - 1; i >= 0; i--) {
    int p = arr[i];
    if (type[p] == 1) {
      (f[p] += cur) %= mod;
    } else if (type[p] == 2) {
      (cur *= val[p]) %= mod;
    } else {
      (f[p] += cur) %= mod, (cur *= mul[p]) %= mod;
    }
  }

  std::vector<i64> add(n);
  [&]() {
    std::queue<int> q;
    for (int i = 0; i < m; i++) {
      if (!deg[i]) { q.push(i); }
    }
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (type[u] == 1) { (add[pos[u]] += f[u] * val[u]) %= mod; }
      i64 cur = f[u];
      std::reverse(link[u].begin(), link[u].end());
      for (auto v : link[u]) {
        (f[v] += cur) %= mod, (cur *= mul[v]) %= mod;
        if (!--deg[v]) { q.push(v); }
      }
    }
  }();

  for (int i = 0; i < n; i++) {
    std::cout << (a[i] * cur + add[i]) % mod << " \n"[i == n - 1];
  }

  return 0;
}