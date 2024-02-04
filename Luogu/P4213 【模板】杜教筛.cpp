/*
 * @file    P4213 【模板】杜教筛.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2024-02-04
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 1e7 + 50;

int prime[N], cnt, lim = 1e7;
i64 phi[N], mu[N];
bool is_not_prime[N];

void init(int _n) {
  phi[1] = mu[1] = 1;
  for (int i = 2; i <= _n; i++) {
    if (!is_not_prime[i]) {
      prime[++cnt] = i;
      phi[i] = i - 1, mu[i] = -1;
    }
    for (int j = 1; j <= cnt && i * prime[j] <= _n; j++) {
      int d = i * prime[j];
      is_not_prime[d] = true;
      phi[d] = phi[i] * phi[prime[j]], mu[d] = -mu[i];
      if (i % prime[j] == 0) {
        phi[d] = phi[i] * prime[j], mu[d] = 0;
        break;
      }
    }
  }
  std::partial_sum(phi + 1, phi + _n + 1, phi + 1);
  std::partial_sum(mu + 1, mu + _n + 1, mu + 1);
}

std::map<i64, i64> s_mu, s_phi;

i64 calc_mu(i64 u) {
  if (u <= lim) return mu[u];
  if (s_mu.count(u)) return s_mu[u];
  i64 res = 1;
  for (i64 i = 2, j; i <= u; i = j + 1) {
    j = u / (u / i);
    res -= calc_mu(u / i) * (j - i + 1);
  }
  return s_mu[u] = res;
}

i64 calc_phi(i64 u) {
  if (u <= lim) return phi[u];
  if (s_phi.count(u)) return s_phi[u];
  i64 res = u * (u + 1) / 2;
  for (i64 i = 2, j; i <= u; i = j + 1) {
    j = u / (u / i);
    res -= calc_phi(u / i) * (j - i + 1);
  }
  return s_phi[u] = res;
}

int n;

void solve() {
  std::cin >> n;
  std::cout << calc_phi(n) << " " << calc_mu(n) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  init(lim);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
