#include <bits/stdc++.h>
using i64 = long long;
int a, b;
signed main() {
  freopen("pour.in", "r", stdin);
  freopen("pour.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> a >> b;
  std::cout << b - a % b << "\n";
  if (a % b == 0) {
    std::cout << 0 << " " << 1 << "\n";
    return 0;
  }
  std::cout << 1 << " " << std::ceil(1. * a / b) << "\n";
  return 0;
}