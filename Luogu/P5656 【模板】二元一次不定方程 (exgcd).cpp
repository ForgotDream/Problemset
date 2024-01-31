/*
 * @file    P5656 【模板】二元一次不定方程 (exgcd).cpp
 * @author  ForgotDream
 * @brief   Math + exGCD
 * @date    2024-01-31
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

i64 a, b, c;

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  }
  i64 d = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}

void solve() {
  std::cin >> a >> b >> c;

  i64 x, y, g = exgcd(a, b, x, y);

  if (c % g) {
    std::cout << -1 << "\n";
    return;
  }

  x *= c / g, y *= c / g;  // 将 gcd(a, b) 放到 c
  i64 p = b / g, q = a / g, k;  // 通解的形式是 x + p * k, y - q * k，这个是熟知的

  if (x < 0) k = std::ceil((1. - x) / p), x += p * k, y -= q * k;
  else k = (x - 1) / p, x -= p * k, y += q * k;

  if (y > 0) {
    std::cout << (y - 1) / q + 1 << " " << x << " " << (y - 1) % q + 1 
              << " " << x + (y - 1) / q * p << " " << y << "\n";
  } else {
    std::cout << x << " " << y + q * i64(std::ceil((1. - y) / q)) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
