/*
 * @file
 * @author  ForgotDream
 * @brief   
 * @date    2025-09-08
 */
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (auto &i : a) std::cin >> i;

  std::sort(a.begin(), a.end(), std::greater<>());

  for (int i = 2; i < n; i++) {
    if (a[i] != a[i - 2] % a[i - 1]) {
      std::cout << -1 << "\n";
      return;
    }
  }

  std::cout << a[0] << " " << a[1] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
