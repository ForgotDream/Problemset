#include <bits/stdc++.h>

using i64 = long long;

constexpr int mod = 1e9 + 7;

i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  while (exp) {
    if (exp & 1) { (res *= base) %= mod; }
    (base *= base) %= mod;
    exp >>= 1;
  }
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int s, t, k;
  std::cin >> s >> t >> k;

  int d = std::abs(t - s);

  if (k < d) {
    std::cout << 0 << "\n";
    return 0;
  } else if (k == d) {
    std::cout << 1 << "\n";
    return 0;
  }

  std::vector<i64> fac(std::max({s, t, k}) + 1);
  fac[0] = 1;
  for (int i = 1; i < fac.size(); i++) { (fac[i] = fac[i - 1] * i) %= mod; }
  auto C = [&](int n, int m) -> i64 { 
    if (n < 0 || m < 0 || m > n) { return 0ll; }
    return fac[n] 
         * fastPow(fac[m], mod - 2, mod) % mod
         * fastPow(fac[n - m], mod - 2, mod) % mod;
  };

  int d1 = 0, d2 = 0;
  /*  d1 -> +, d2 -> - */
  i64 ans = 0;
  (s < t ? d1 : d2) = d;
  for (int i = d; i <= k; i += 2) {
    int t = 2 * d2 - 1 - s;
    (ans += C(i, d1) - C(t, d2)) %= mod;
    d1++, d2++;
  }

  std::cout << ans << "\n";

  return 0;
}

/**
 * 任意时刻不能出现 d2 >= d1 + s 的情况
 * 这意味着什么？
 */
