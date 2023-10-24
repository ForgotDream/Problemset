/**
 * @file    B3695 集合运算 3.cpp
 * @author  ForgotDream
 * @brief   Bitset + Bitwise Calculation
 * @date    2023-05-04
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

constexpr int N = 3e4 + 50;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, q;
  std::cin >> n >> m >> q;

  std::vector<std::bitset<N>> s(n);
  for (int i = 0; i < n; i++) {
    int c;
    std::cin >> c;
    for (int j = 0; j < c; j++) {
      int u;
      std::cin >> u;
      s[i][u - 1] = true;
    }
  }

  std::bitset<N> mask;
  for (int i = 0; i < m; i++) {
    mask[i] = true;
  }

  while (q--) {
    int opt, x, y;
    std::cin >> opt >> x >> y;
    x--, y--;
    if (opt == 1) {
      s[x] <<= y + 1;
      s[x] &= mask;
    } else if (opt == 2) {
      s[x] >>= y + 1;
    } else if (opt == 3) {
      std::cout << (s[x] & s[y]).count() << "\n";
    } else if (opt == 4) {
      std::cout << (s[x] | s[y]).count() << "\n";
    } else {
      std::cout << (s[x] ^ s[y]).count() << "\n";
    }
  }

  return 0;
}