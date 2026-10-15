/*
 * @file
 * @author  ForgotDream
 * @brief   
 * @date    2025-09-08
 */
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 5e5;
constexpr int mod = 1e9 + 7;

i64 fac[N + 5], ifc[N + 5];

i64 fast_pow(i64 base, i64 exp) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) res = res * base % mod;
    base = base * base % mod;
  }
  return res;
}

void init() {
  fac[0] = 1;
  for (int i = 1; i <= N; i++) fac[i] = i * fac[i - 1] % mod;
  ifc[N] = fast_pow(fac[N], mod - 2);
  for (int i = N - 1; ~i; i--) ifc[i] = (i + 1) * ifc[i + 1] % mod;
}

i64 C(i64 n, i64 m) {
  if (m < 0 || n < m) return 0;
  return fac[n] * ifc[m] % mod * ifc[n - m] % mod;
}

void solve() {
  int n;
  std::cin >> n;

  std::vector<i64> a(n + 1);
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  auto work = [&](auto &&self, int lo, int hi) -> i64 {
    if (lo > hi) return 1;

    int mid = -1;
    for (int t = 0; t <= hi - lo; t++) {
      int k;
      if (t % 2) k = hi - t / 2;
      else k = lo + t / 2;
      i64 cur = 1ll * (k - lo + 1) * (hi - k + 1);
      if (cur == a[k]) {
        mid = k;
        break;
      }
    }

    if (mid == -1) return 0;

    i64 res = self(self, lo, mid - 1) * self(self, mid + 1, hi) % mod;
    res = res * C(hi - lo, mid - lo) % mod;

    return res;
  };

  std::cout << work(work, 1, n) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  init();

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
