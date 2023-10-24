/**
 * @file    P1292 倒酒.cpp
 * @author  ForgotDream
 * @brief   Math + exgcd
 * @date    2023-08-09
 */
#include <bits/stdc++.h>
using i64 = long long;
int a, b;
int exgcd(int a, int b, int &x, int &y) {
  if (!b) return x = 1, y = 0, a;
  int d = exgcd(b, a % b, y, x);
  y -= a/ b * x;
  return d;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> a >> b;
  int x, y, g;
  std::cout << (g = exgcd(a, b, x, y)) << "\n";
  x *= -1, a *= -1;
  while (x < 0 || y < 0) {
    x += b / g * (x < 0);
    y -= a / g * (x >= 0);
  }
  std::cout << x << " " << y << "\n";
  return 0;
}