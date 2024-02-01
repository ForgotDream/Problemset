/*
 * @file    P1829 [国家集训队] Crash的数字表格 JZPTAB.cpp
 * @author  ForgotDream
 * @brief   Math + Mobius Inversion
 * @date    2024-02-01
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 1e7 + 50, mod = 20101009;

int n, m;

int prime[N], mu[N], cnt;
i64 s[N];
bool is_not_prime[N];

void get_mu(int _n) {
  mu[1] = 1;
  for (int i = 2; i <= _n; i++) {
    if (!is_not_prime[i]) mu[i] = -1, prime[++cnt] = i;
    for (int j = 1; j <= cnt && i * prime[j] <= _n; j++) {
      is_not_prime[i * prime[j]] = true;
      mu[i * prime[j]] = -1 * mu[i];
      if (i % prime[j] == 0) {
        mu[i * prime[j]] = 0;
        break;
      }
    }
  }
  for (int i = 1; i <= _n; i++) {
    s[i] = s[i - 1] + 1ll * i * i % mod * (mu[i] + mod) % mod;
    s[i] %= mod;
  }
}

inline i64 sum(i64 x, i64 y) {
  return (x * (x + 1) / 2 % mod) * (y * (y + 1) / 2 % mod) % mod;
}

inline i64 calc(i64 x, i64 y) {
  i64 res = 0;
  for (int i = 1, j; i <= std::min(x, y); i = j + 1) {
    j = std::min(x / (x / i), y / (y / i));
    res += (s[j] - s[i - 1] + mod) % mod * sum(x / i, y / i) % mod;
    res %= mod;
  }
  return res;
}

inline i64 solve(i64 x, i64 y) {
  i64 res = 0;
  for (int i = 1, j; i <= std::min(x, y); i = j + 1) {
    j = std::min(x / (x / i), y / (y / i));
    res += 1ll * (j - i + 1) * (i + j) / 2 % mod * calc(x / i, y / i) % mod;
    res %= mod;
  }
  return res;
}

void solve() {
  std::cin >> n >> m;
  get_mu(std::min(n, m));
  std::cout << solve(n, m) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
