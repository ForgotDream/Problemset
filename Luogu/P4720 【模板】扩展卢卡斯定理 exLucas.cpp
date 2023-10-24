/**
 * @file    P4720 【模板】扩展卢卡斯定理/exLucas.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-11
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1050;
i64 n, m, p;
i64 a[N], b[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (!b) return x = 1, y = 0, a;
  i64 d = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}
i64 inv(i64 num, i64 mod) {
  i64 x, y;
  exgcd(num, mod, x, y);
  return (x + mod) % mod;
}
i64 f(i64 n, i64 p, i64 pk) {
  if (!n) return 1;
  i64 cir = 1, rst = 1;
  for (i64 i = 1; i <= pk; i++) {
    if (i % p) (cir *= i % pk) %= pk;
  }
  cir = fastPow(cir, n / pk, pk);
  for (i64 i = pk * (n / pk); i <= n; i++) {
    if (i % p) (rst *= i % pk) %= pk;
  }
  return f(n / p, p, pk) * cir % pk * rst % pk;
}
i64 g(i64 n, i64 p) {
  i64 res = 0, cpy = p;
  for (; p <= n; p *= cpy) res += n / p;
  return res;
}
i64 C(i64 n, i64 m, i64 p, i64 pk) {
  i64 a = f(n, p, pk), b = inv(f(m, p, pk), pk), c = inv(f(n - m, p, pk), pk);
  return a * b % pk * c % pk * 
         fastPow(p, g(n, p) - g(m, p) - g(n - m, p), pk) % pk;
}
i64 exLucas(i64 n, i64 m, i64 mod) {
  i64 cpy = mod, res = 0;
  int cnt = 0;
  for (i64 i = 2; i * i <= cpy; i++) {
    if (cpy % i == 0) {
      i64 pk = 1;
      while (cpy % i == 0) cpy /= i, pk *= i;
      a[++cnt] = pk, b[cnt] = C(n, m, i, pk);
    }
  }
  if (cpy != 1) a[++cnt] = cpy, b[cnt] = C(n, m, cpy, cpy);
  for (int i = 1; i <= cnt; i++) {
    i64 k = mod / a[i], t = inv(k, a[i]);
    (res += b[i] * k % mod * t % mod) %= mod;
  }
  return res;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m >> p;
  std::cout << exLucas(n, m, p) << "\n";
  return 0;
}