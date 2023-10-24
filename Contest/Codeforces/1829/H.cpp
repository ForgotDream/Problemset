#include <bits/stdc++.h>

using i64 = long long;

constexpr int MOD = 1e9 + 7;

void solve() {
  int n, k;
  std::cin >> n >> k;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector f(n, std::vector<i64>(65));
  f[0][a[0]] = 1;
  f[0][0] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < 64; j++) {
      f[i][j] += f[i - 1][j];
    }
    for (int j = 0; j < 64; j++) {
      (f[i][j & a[i]] += f[i - 1][j]) %= MOD;
    }
    (f[i][a[i]] += 1) %= MOD;
  }

  i64 ans = 0;
  for (int i = 0; i < 64; i++) {
    if (__builtin_popcount(i) == k) {
      (ans += f[n - 1][i]) %= MOD;
    }
  }

  std::cout << ans << "\n";

  return;
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