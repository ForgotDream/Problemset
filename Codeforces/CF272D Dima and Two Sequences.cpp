/**
 * @file    CF272D Dima and Two Sequences.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-08-15
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e6 + 50;
int n;
i64 a[N], b[N], mod;
std::vector<int> c;
i64 f[N], g[N];
i64 ans;
i64 calc(i64 f, i64 g) {
  i64 res = 1;
  for (int i = 1; i <= f; i++) {
    if (i % 2 == 0 && g) (res *= i / 2) %= mod, g--;
    else (res *= i) %= mod;
  }
  return res;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], c.push_back(a[i]);
  for (int i = 1; i <= n; i++) std::cin >> b[i], c.push_back(b[i]);
  std::cin >> mod;
  std::sort(c.begin(), c.end());
  c.erase(std::unique(c.begin(), c.end()), c.end());
  for (int i = 1; i <= n; i++) {
    int u = std::lower_bound(c.begin(), c.end(), a[i]) - c.begin();
    f[u + 1]++;
    int v = std::lower_bound(c.begin(), c.end(), b[i]) - c.begin();
    f[v + 1]++;
    if (u == v) g[u + 1]++; 
  }
  ans = 1;
  for (int i = 1; i <= c.size(); i++) (ans *= calc(f[i], g[i])) %= mod;
  std::cout << ans << "\n";
  return 0;
}