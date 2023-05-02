#include <bits/stdc++.h>

using i64 = long long;

constexpr int MOD = 998244353;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<int> pow(n);
  pow[0] = 1;
  for (int i = 1; i < n; i++) {
    (pow[i] = 10 * pow[i - 1]) %= MOD;
  }
  for (int i = 1; i < n; i++) {
    pow[i] += pow[i - 1];
    pow[i] %= MOD;
  }

  int fact = 1;
  for (int i = 1; i < n; i++) {
    fact *= i;
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    (ans += (i64) a[i] * pow[n - 1] * fact % MOD) %= MOD;
  }

  std::cout << ans << "\n";

  return 0;
}