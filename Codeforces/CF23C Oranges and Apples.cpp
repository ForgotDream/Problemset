/**
 * @file    CF23C Oranges and Apples.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-23
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using i64 = long long;
using ti3 = std::tuple<int, int, int>;

constexpr int N = 2e5 + 50;
int n;
ti3 a[N];
i64 sodd, seven;
void solve() {
  std::cin >> n;
  for (int i = 1; i <= 2 * n - 1; ++i) {
    auto &[ac, bc, idx] = a[i];
    std::cin >> ac >> bc, idx = i;
  }
  std::sort(a + 1, a + 2 * n, std::greater<ti3>());
  sodd = seven = 0;
  for (int i = 1; i <= 2 * n - 1; i += 2) {
    sodd += std::get<1>(a[i]);
    if (i < 2 * n - 1) seven += std::get<1>(a[i + 1]);
  }
  std::cout << "YES\n";
  if (sodd > seven) {
    for (int i = 1; i <= 2 * n - 1; i += 2) {
      std::cout << std::get<2>(a[i]) << " ";
    }
  } else {
    std::cout << std::get<2>(a[1]) << " ";
    for (int i = 2; i <= 2 * n - 1; i += 2) {
      std::cout << std::get<2>(a[i]) << " ";
    }
  }
  std::cout << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--) solve();
  return 0;
}