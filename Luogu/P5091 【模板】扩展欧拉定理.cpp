/*
 * @file    P5091 【模板】扩展欧拉定理.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2024-01-31
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

int a, m, b;

bool read(int &u, int mod) {
  char c = std::cin.get();
  bool flg = false;
  u = 0;
  while (!std::isdigit(c)) c = std::cin.get();
  while (std::isdigit(c)) {
    u = 10 * u + (c - '0');
    if (u >= mod) u %= mod, flg = true;
    c = std::cin.get();
  }
  return flg;
}

i64 fast_pow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}

void solve() {
  std::cin >> a >> m;

  int copy = m, phi = m;
  for (int i = 2; i * i <= copy; i++) {
    if (copy % i == 0) {
      phi /= i, phi *= i - 1;
      while (copy % i == 0) copy /= i;
    }
  }
  if (copy > 1) phi /= copy, phi *= copy - 1;

  bool flg = read(b, phi);
  if (flg) {
    std::cout << fast_pow(a, b + phi, m) << "\n";
  } else {
    std::cout << fast_pow(a, b, m) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
