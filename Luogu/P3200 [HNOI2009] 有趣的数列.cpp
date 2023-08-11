/**
 * @file    P3200 [HNOI2009] 有趣的数列.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-11
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2e6 + 50;
int n, p;
i64 a = 1, b = 1;
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
int prime[N], lowFac[N], pcnt;
bool isNotPrime[N];
void getPrime(int num) {
  for (int i = 2; i <= num; i++) {
    if (!isNotPrime[i]) prime[++pcnt] = i, lowFac[i] = i;
    for (int j = 1; j <= pcnt && i * prime[j] <= num; j++) {
      lowFac[i * prime[j]] = prime[j];
      isNotPrime[i * prime[j]] = true;
      if (i % prime[j] == 0) break;
    }
  }
}
int cnt[N], ans = 1;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> p;
  getPrime(2 * n);
  for (int i = 1; i <= n; i++) cnt[i] = -1;
  for (int i = n + 2; i <= 2 * n; i++) cnt[i] = 1;
  for (int i = 2 * n; i >= 2; i--) {
    if (lowFac[i] != i) cnt[lowFac[i]] += cnt[i], cnt[i / lowFac[i]] += cnt[i];
  }
  for (int i = 1; i <= pcnt; i++) {
    ans = 1ll * ans * fastPow(prime[i], cnt[prime[i]], p) % p;
  }
  std::cout << ans << "\n";
  return 0;
}