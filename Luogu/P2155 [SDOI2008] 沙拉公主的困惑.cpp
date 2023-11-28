/**
 * @file    P2155 [SDOI2008] 沙拉公主的困惑.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-11-22
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 1e7 + 50;
int n, m, mod;
bool isNotPrime[N];
int prime[N], cnt, pi[N];
void getPrime(int n) {
  isNotPrime[1] = true;
  for (int i = 2; i <= n; i++) {
    pi[i] = pi[i - 1];
    if (!isNotPrime[i]) prime[++cnt] = i, pi[i]++;
    for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
      isNotPrime[i * prime[j]] = true;
      if (i % prime[j] == 0) break;
    }
  }
}
int fac[N], inv[N], ifc[N], phi[N];
void init() {
  getPrime(1e7);
  int lim = std::min(int(1e7), mod - 1);
  inv[1] = 1;
  for (int i = 2; i <= lim; i++) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
  phi[0] = 1;
  for (int i = 1; i <= cnt; i++) phi[i] = 1ll * phi[i - 1] * (prime[i] - 1) % mod;
  ifc[0] = 1;
  for (int i = 1; i <= cnt; i++) {
    ifc[i] = ifc[i - 1];
    if (prime[i] != mod) ifc[i] = 1ll * ifc[i] * inv[prime[i] % mod] % mod;
  }
  fac[0] = 1;
  for (int i = 1; i <= 1e7; i++) {
    fac[i] = fac[i - 1];
    if (i != mod) fac[i] = 1ll * i * fac[i] % mod;
  }
}
void solve() {
  std::cin >> n >> m;
  if (n >= mod && m < mod) std::cout << 0 << "\n";
  else std::cout << 1ll * fac[n] * ifc[pi[m]] % mod * phi[pi[m]] % mod << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t >> mod;
  init();
  while (t--) solve();
  return 0;
}
