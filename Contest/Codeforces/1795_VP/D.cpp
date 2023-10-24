#include <iostream>

using i64 = long long;

constexpr int N = 3e5 + 50, mod = 998244353;
int n, w[N];
i64 ans = 1;

i64 fac[N], inv[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void init() {
  fac[0] = inv[0] = 1;
  for (int i = 1; i <= n / 3; i++) {
    fac[i] = i * fac[i - 1] % mod;
    inv[i] = fastPow(fac[i], mod - 2, mod);
  }
}
i64 C(i64 n, i64 m) { return fac[n] * inv[m] % mod * inv[n - m] % mod; }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> w[i];

  init();

  for (int i = 1; i <= n; i += 3) {
    int a[3] = {w[i], w[i + 1], w[i + 2]};
    std::sort(a, a + 3);
    if (a[0] == a[1] && a[1] == a[2]) (ans *= 3) %= mod;
    else if (a[0] == a[1]) (ans *= 2) %= mod;
  }
  (ans *= C(n / 3, n / 6)) %= mod;

  std::cout << ans << "\n";

  return 0;
}