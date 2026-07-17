/*
 * @file
 * @author  ForgotDream
 * @brief   
 * @date    2025-09-08
 */
#include <iostream>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  int a[] = {0, 1, 0, 1, 1, 0, 0, 1};
  int b[] = {0, 0, 1, 0, 1, 2, 0, 2, 1, 1, 2, 2};

  if (n % 2 == 1) {
    for (int i = 1; i <= n - 3; i += 2) {
      for (int j = 0; j < 8; j++) std::cout << i + a[j] << " ";
    }
    for (int j = 0; j < 12; j++) {
      std::cout << n - 2 + b[j] << " ";
    }
    std::cout << "\n";
  } else {
    for (int i = 1; i <= n; i += 2) {
      for (int j = 0; j < 8; j++) std::cout << i + a[j] << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
