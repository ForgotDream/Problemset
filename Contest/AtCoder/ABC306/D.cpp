#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<i64> x(n), y(n);
  for (int i = 0; i < n; i++) { std::cin >> x[i] >> y[i]; }

  std::vector f(n, std::vector<i64>(2));
  if (!x[0]) {
    f[0][0] = std::max(0ll, y[0]);
  } else {
    f[0][1] = y[0];
  }
  for (int i = 1; i < n; i++) {
    if (x[i]) {
      f[i][1] = std::max(f[i - 1][1], f[i - 1][0] + y[i]);
      f[i][0] = f[i - 1][0];
    } else {
      f[i][0] = std::max({f[i - 1][0] + y[i], f[i - 1][1] + y[i], f[i - 1][0]});
      f[i][1] = f[i - 1][1];
    }
  }
  std::cout << std::max(f[n - 1][0], f[n - 1][1]) << "\n";

  return 0;
}