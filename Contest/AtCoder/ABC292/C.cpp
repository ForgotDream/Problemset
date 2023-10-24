#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int n;
  std::cin >> n;

  std::vector<int> factor(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= sqrt(i); j++) {
      if (i % j != 0) {
        continue;
      }
      factor[i]++;
      if (j != sqrt(i)) {
        factor[i]++;
      }
    }
    // std::cerr << factor[i] << "\n";
  }

  i64 ans = 0;
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= (double) n / i; j++) {
      int rst = n - i * j;
      ans += factor[rst];
    }
  }

  std::cout << ans << "\n";

  return 0;
}