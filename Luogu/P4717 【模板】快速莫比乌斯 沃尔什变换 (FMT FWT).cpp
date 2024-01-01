/*
 * @file    P4717 【模板】快速莫比乌斯/沃尔什变换 (FMT/FWT).cpp
 * @author  ForgotDream
 * @brief   FMT / FWT
 * @date    2023-12-30
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50, mod = 998244353;
constexpr int inv2 = (mod + 1) / 2;
int n;
i64 a[N], b[N], ta[N], tb[N], c[N];

void FWTOr(i64 *a, int n, int opt) {
  for (int i = 1, d = 2; i < n; i <<= 1, d <<= 1) {
    for (int j = 0; j < n; j += d) {
      for (int k = 0; k < i; k++) {
        (a[i + j + k] += a[j + k] * opt + mod) %= mod;
      }
    }
  }
}
void FWTAnd(i64 *a, int n, int opt) {
  for (int i = 1, d = 2; i < n; i <<= 1, d <<= 1) {
    for (int j = 0; j < n; j += d) {
      for (int k = 0; k < i; k++) {
        (a[j + k] += a[i + j + k] * opt + mod) %= mod;
      }
    }
  }
}
void FWTXor(i64 *a, int n, int opt) {
  for (int i = 1, d = 2; i < n; i <<= 1, d <<= 1) {
    for (int j = 0; j < n; j += d) {
      for (int k = 0; k < i; k++) {
        int x = a[j + k], y = a[i + j + k];
        a[j + k] = (x + y) % mod, a[i + j + k] = (x - y + mod) % mod;
        if (opt == -1) (a[j + k] *= inv2) %= mod, (a[i + j + k] *= inv2) %= mod;
      }
    }
  }
}

void solve() {
  std::cin >> n;
  int m = (1 << n);
  for (int i = 0; i < m; i++) std::cin >> a[i];
  for (int i = 0; i < m; i++) std::cin >> b[i];

  std::copy(a, a + m, ta), std::copy(b, b + m, tb);

  FWTOr(a, m, 1), FWTOr(b, m, 1);
  for (int i = 0; i < m; i++) c[i] = a[i] * b[i] % mod;
  FWTOr(c, m, -1);
  for (int i = 0; i < m; i++) std::cout << c[i] << " \n"[i == m - 1];

  std::copy(ta, ta + m, a), std::copy(tb, tb + m, b);
  FWTAnd(a, m, 1), FWTAnd(b, m, 1);
  for (int i = 0; i < m; i++) c[i] = a[i] * b[i] % mod;
  FWTAnd(c, m, -1);
  for (int i = 0; i < m; i++) std::cout << c[i] << " \n"[i == m - 1];

  std::copy(ta, ta + m, a), std::copy(tb, tb + m, b);
  FWTXor(a, m, 1), FWTXor(b, m, 1);
  for (int i = 0; i < m; i++) c[i] = a[i] * b[i] % mod;
  FWTXor(c, m, -1);
  for (int i = 0; i < m; i++) std::cout << c[i] << " \n"[i == m - 1];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
