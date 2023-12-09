/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-12-09
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 35, M = 2e3 + 50, mod = 998244353;
int n, m, c[M];
i64 a[N][N];
int u[M], v[M], w[M];
std::vector<int> b[M];
inline i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
inline i64 getInv(i64 u) { return fastPow(u, mod - 2, mod); }
i64 det(i64 a[N][N]) {
  i64 res = 1, flg = 1;
  for (int i = 1; i < n; i++) {
    int p = -1;
    for (int j = i; j < n; j++) {
      if (a[j][i]) {
        p = j;
        break;
      }
    }
    if (p == -1) return 0;
    if (i != p) std::swap(a[i], a[p]), flg = -flg;
    res = res * a[i][i] % mod;
    i64 inv = getInv(a[i][i]);
    for (int j = i + 1; j < n; j++) a[i][j] = a[i][j] * inv % mod;
    for (int j = i + 1; j < n; j++) {
      if (!a[j][i]) continue;
      for (int k = i + 1; k < n; k++) {
        a[j][k] = (a[j][k] - a[j][i] * a[i][k] % mod + mod) % mod;
      }
    }
  }
  return res;
}
int prime[M], mu[M], cnt;
bool isNotPrime[N];
void getMu(int n) {
  mu[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) prime[++cnt] = i, mu[i] = -1;
    for (int j = 1; j <= cnt && i * prime[j]; j++) {
      isNotPrime[i * prime[j]] = true;
      mu[i * prime[j]] = mu[i] * -1;
      if (i % prime[j] == 0) {
        mu[i * prime[j]] = 0;
        break;
      }
    }
  }
}
void solve() {
  std::cin >> n >> m;
  int mx = 0;
  for (int i = 1; i <= m; i++) {
    std::cin >> u[i] >> v[i] >> w[i];
    mx = std::max(mx, w[i]), c[w[i]]++;
    b[w[i]].push_back(i);
  }
  getMu(mx);
  for (int i = mx; i; i--) {
    for (int j = 2 * i; j <= mx; j += i) c[i] += -mu[j / i] * c[j];
    for (int j = 2 * i; j <= mx; j += i) {
      if (c[i] == c[j]) {
        c[i] = 0;
        break;
      }
    }
  }
  for (int i = 1; i <= mx; i++) std::cerr << mu[i] << " " << c[i] << "\n";
  i64 ans = 0;
  for (int i = 1; i <= mx; i++) {
    if (c[i] < n - 1) continue;
    memset(a, 0, sizeof(a));
    for (int j = i; j <= mx; j += i) {
      for (auto k : b[j]) {
        a[u[k]][u[k]] += w[k], a[v[k]][v[k]] += w[k];
        a[u[k]][v[k]] -= w[k], a[v[k]][u[k]] -= w[k];
      }
    }
    ans += i * det(a);
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
