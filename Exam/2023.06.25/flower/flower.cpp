#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

int main() {
  freopen("flower.in", "r", stdin);
  freopen("flower.out", "w", stdout);

  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout << std::fixed << std::setprecision(12);

  int n, k;
  std::cin >> n >> k;

  std::vector<f80> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<i64> pw(n + 1);
  for (int i = 1; i <= n; i++) {
    pw[i] = 1;
    for (int j = 0; j < k; j++) {
      pw[i] *= i;
    }
  }

  std::vector<f80> f(n);
  for (int i = 0; i < n; i++) {
    f80 cur = 1;
    for (int j = i; j >= 0; j--) {
      f[i] += (cur * (1 - a[j])) * ((j >= 1 ? f[j - 1] : 0) + pw[i - j]);
      cur *= a[j];
    }
    f[i] += cur * pw[i + 1];
  }

  std::cout << f[n - 1] << "\n";

  return 0;
}