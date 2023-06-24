#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    int sum = 0;
    for (int j = 0; j < 7; j++) {
      int cur;
      std::cin >> cur;
      sum += cur;
    }
    std::cout << sum << " \n"[i == n - 1];
  }

  return 0;
}