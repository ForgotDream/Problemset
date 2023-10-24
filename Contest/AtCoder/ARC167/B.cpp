#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using i64 = long long;
using pii = std::pair<i64, i64>;

constexpr i64 mod = 998244353;
i64 a, b;
std::vector<pii> fac;
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
i64 inv(i64 u) { return fastPow(u, mod - 2, mod); }
void solve() {
  std::cin >> a >> b;
  bool flg = (b % 2 == 0);
  b %= mod;
  i64 cpy = a;
  for (i64 i = 2; 1ll * i * i <= cpy; i++) {
    if (cpy % i == 0) {
      fac.emplace_back(i, 0);
      while (cpy % i == 0) cpy /= i, fac.back().second++;
      if (fac.back().second % 2 == 1) flg = true;
      fac.back().second = fac.back().second * b % mod;
    }
  }
  if (cpy != 1) fac.emplace_back(cpy, b), flg = true;
  i64 prod = 1;
  for (auto i : fac) prod = prod * (i.second + 1) % mod;
  prod = b * prod % mod;
  if (!flg) prod = (prod - 1 + mod) % mod;
  std::cout << prod * inv(2) % mod << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
