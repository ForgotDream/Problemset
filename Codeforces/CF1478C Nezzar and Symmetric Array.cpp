/**
 * @file    CF1478C Nezzar and Symmetric Array.cpp
 * @author  ForgotDream
 * @brief   构造
 * @date    2023-08-29
 */
#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n;
i64 a[N], b[N], d[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= 2 * n; i++) std::cin >> a[i];
  std::sort(a + 1, a + 2 * n + 1, std::greater<i64>());
  for (int i = 1; i <= n; i++) {
    if (a[2 * i - 1] != a[2 * i]) {
      std::cout << "NO\n";
      return;
    }
    b[i] = a[2 * i];
  }
  for (int i = 2; i <= n; i++) {
    if (b[i - 1] == b[i] || (b[i - 1] - b[i]) % (2 * (n - i + 1))) {
      std::cout << "NO\n";
      return;
    }
    d[i] = (b[i - 1] - b[i]) / (2 * (n - i + 1));
  }
  for (int i = 2; i <= n; i++) b[n] -= 2 * (i - 1) * d[i];
  if (b[n] <= 0 || b[n] % (2 * n)) {
    std::cout << "NO\n";
    return;
  }
  std::cout << "YES\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}