/**
 * @file    P3599 Koishi Loves Construction.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-10-20
 */
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50;
int typ, n;
// --- Prime Utils ---
int prime[N], cnt;
bool isNotPrime[N];
void init(int n) {
  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) prime[++cnt] = i;
    for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
      isNotPrime[i * prime[j]] = true;
      if (i % prime[j] == 0) break;
    }
  }
}
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
i64 inv(i64 base, i64 mod) { return fastPow(base, mod - 2, mod); }
// -------------------
void solve() {
  std::cin >> n;
  if (typ == 1) {
    if (n % 2 && n > 1) {
      std::cout << 0 << "\n";
      return;
    }
    std::cout << 2 << " ";
    for (int i = 1; i <= n; i++) {
      if (i & 1) std::cout << n - i + 1 << " \n"[i == n];
      else std::cout << i - 1 << " \n"[i == n];
    }
  } else {
    init(n);
    if (isNotPrime[n] && n != 1 && n != 4) {
      std::cout << 0 << "\n";
      return;
    }
    std::cout << 2 << " ";
    if (n == 1) {
      std::cout << 1 << "\n";
      return;
    } else if (n == 4) {
      std::cout << 1 << " " << 3 << " " << 2 << " " << 4 << "\n";
      return;
    }
    int prod = 1, cur = 1;
    for (int i = 1; i < n; i++) {
      std::cout << cur << " ";
      cur = 1ll * inv(prod, n) * (i + 1) % n;
      prod = 1ll * prod * cur % n;
    }
    std::cout << n << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> typ >> t;
  while (t--) solve();
  return 0;
}
