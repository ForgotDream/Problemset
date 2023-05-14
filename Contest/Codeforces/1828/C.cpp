#include <bits/stdc++.h>

using i64 = long long;

constexpr int mod = 1e9 + 7;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    std::cin >> b[i];
  }

  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());

  for (int i = 0; i < n; i++) {
    if (a[i] <= b[i]) {
      std::cout << 0 << "\n";
      return;
    }
  }

  std::vector<i64> f(n);
  f[0] = 1;
  for (int i = 1; i < n; i++) {
    auto it = std::upper_bound(a.begin(), a.begin() + i + 1, b[i]);
    (f[i] = f[i - 1] * (a.begin() + i + 1 - it)) %= mod;
  }

  std::cout << f[n - 1] << "\n";

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