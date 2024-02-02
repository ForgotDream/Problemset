/*
 * @file    P6620 [省选联考 2020 A 卷] 组合数问题.cpp
 * @author  ForgotDream
 * @brief   Math + Stirling Number / Polygon
 * @date    2024-02-02
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 1010;

int n, x, p, m;
int a[N], s[N][N];

inline i64 fast_pow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}

void solve() {
  std::cin >> n >> x >> p >> m;
  for (int i = 0; i <= m; i++) std::cin >> a[i];

  s[1][1] = 1;
  for (int i = 2; i <= m; i++) {
    for (int j = 1; j <= i; j++) {
      s[i][j] = (1ll * j * s[i - 1][j] % p + s[i - 1][j - 1]) % p;
    }
  }

  i64 ans = a[0] * fast_pow((x + 1) % p, n, p) % p;
  for (int i = 1; i <= m; i++) {
    int tmp = 1ll * fast_pow(x % p, i, p) * fast_pow((x + 1) % p, n - i, p) % p;
    int val = 0;
    for (int j = 0; j <= i - 1; j++) tmp = 1ll * tmp * (n - j) % p;
    for (int j = i; j <= m; j++) {
      val = (val + 1ll * s[j][i] * a[j] % p) % p;
    }
    ans = (ans + 1ll * val * tmp) % p;
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
