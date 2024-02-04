/*
 * @file    P5491 【模板】二次剩余.cpp
 * @author  ForgotDream
 * @brief   Cipolla
 * @date    2024-02-04
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using comp = std::complex<i64>;

std::random_device rd;
std::mt19937_64 rng(rd());

int n, p;

i64 eye;

struct Complex {
  i64 real, imag;
  Complex(i64 _r = 0, i64 _i = 0) : real(_r), imag(_i) {}
};

bool operator==(const Complex &lhs, const Complex &rhs) {
  return lhs.real == rhs.real && lhs.imag == rhs.imag;
}

Complex operator*(const Complex &lhs, const Complex &rhs) {
  return Complex((lhs.real * rhs.real + eye * lhs.imag % p * rhs.imag) % p,
                 (lhs.real * rhs.imag + lhs.imag * rhs.real) % p);
}

inline Complex fast_pow(Complex base, i64 exp) {
  Complex res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) res = res * base;
    base = base * base;
  }
  return res;
}

inline bool chk(int u) {
  return fast_pow(u, (p - 1) / 2) == 1;
}

i64 cipolla(i64 n, i64 p) {
  n %= p;
  if (fast_pow(n, (p - 1) / 2) == p - 1) return -1;

  i64 a = rng() % p;
  while (!a || chk((a * a - n + p) % p)) a = rng() % p;

  eye = (a * a - n + p) % p;
  return fast_pow(Complex(a, 1), (p + 1) / 2).real;
}

void solve() {
  std::cin >> n >> p;

  if (n == 0) {
    std::cout << "0\n";
    return;
  }

  i64 ans = cipolla(n, p);

  if (ans == -1) {
    std::cout << "Hola!\n";
  } else {
    i64 ano = p - ans;
    if (ans > ano) std::swap(ans, ano);
    std::cout << ans << " " << (p - ans) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
