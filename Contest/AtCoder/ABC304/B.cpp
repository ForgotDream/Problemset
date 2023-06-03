#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  int digit = 1;
  while (1000 * digit <= n) {
    digit *= 10;
  }

  std::cout << n / digit * digit << "\n";

  return 0;
}