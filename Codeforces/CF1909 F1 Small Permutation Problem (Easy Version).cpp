/*
 * @file    CF1909 F1 Small Permutation Problem (Easy Version).cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-12-24
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50, mod = 998244353;
int n, a[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  if (a[n] != n || a[1] > 1) return std::cout << 0 << "\n", void();

  int j = 0;
  i64 ans = 1;
  for (int i = n; i >= 1; i--) {
    int d = a[i] - a[i - 1];
    if (d < 0 || d > 2) return std::cout << 0 << "\n", void();

    if (d == 0) j--;
    else if (d == 1) ans = ans * (i + j - a[i - 1]) % mod;
    else ans = ans * (j + 1) % mod * (i - 1 - a[i - 1]) % mod, j++;
  }

  if (j != 0) return std::cout << 0 << "\n", void();

  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
