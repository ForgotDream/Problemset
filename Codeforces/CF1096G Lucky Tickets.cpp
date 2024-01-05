/*
 * @file    CF1096G Lucky Tickets.cpp
 * @author  ForgotDream
 * @brief   DP + FFT
 * @date    2024-01-04
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 50, mod = 998244353;

inline i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
template<i64 MOD>
struct ModInt {
  i64 val;
  explicit operator i64() { return val; }
  ModInt(i64 v = 0) : val(v % MOD) {}
  bool operator==(const ModInt<MOD> &rhs) const { return val == rhs.val; }
  bool operator!=(const ModInt<MOD> &rhs) const { return !(val == rhs.val); }
  bool operator<(const ModInt<MOD> &rhs) const { return val < rhs.val; }
  bool operator>(const ModInt<MOD> &rhs) const { return !(*this < rhs) && !(*this == rhs); }
  static i64 getInv(i64 u) { return fastPow(u, MOD - 2, MOD); }
  ModInt<MOD> &operator+=(const ModInt<MOD> &rhs) {
    val = (val + rhs.val) % MOD;
    return *this;
  }
  ModInt<MOD> &operator-=(const ModInt<MOD> &rhs) {
    val = (val - rhs.val + MOD) % MOD;
    return *this;
  }
  ModInt<MOD> &operator*=(const ModInt<MOD> &rhs) {
    val = (val * rhs.val) % MOD;
    return *this;
  }
  ModInt<MOD> &operator/=(const ModInt<MOD> &rhs) {
    val = (val * getInv(rhs.val)) % MOD;
    return *this;
  }
  ModInt<MOD> &operator++() { return *this += 1; }
  ModInt<MOD> &operator--() { return *this -= 1; }
  ModInt<MOD> operator++(int) {
    auto cur = *this;
    ++(*this);
    return cur;
  }
  ModInt<MOD> operator--(int) {
    auto cur = *this;
    --(*this);
    return cur;
  }
  friend ModInt<MOD> operator+(const ModInt<MOD> &lhs, const ModInt<MOD> &rhs) {
    return ModInt<MOD>((lhs.val + rhs.val) % MOD);
  }
  friend ModInt<MOD> operator-(const ModInt<MOD> &lhs, const ModInt<MOD> &rhs) {
    return ModInt<MOD>((lhs.val - rhs.val + MOD) % MOD);
  }
  friend ModInt<MOD> operator*(const ModInt<MOD> &lhs, const ModInt<MOD> &rhs) {
    return ModInt<MOD>((lhs.val * rhs.val) % MOD);
  }
  friend ModInt<MOD> operator/(const ModInt<MOD> &lhs, const ModInt<MOD> &rhs) {
    return ModInt<MOD>((lhs.val * getInv(rhs.val)) % MOD);
  }
};
template<i64 MOD>
std::istream &operator>>(std::istream &is, ModInt<MOD> &mint) {
  is >> mint.val;
  return is;
}
template<i64 MOD>
std::ostream &operator<<(std::ostream &os, const ModInt<MOD> &mint) {
  os << mint.val;
  return os;
}

using Z = ModInt<mod>;

int n, k, a[20];

Z f[N], g[N], inv[N], ans = 1;

void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= k; i++) std::cin >> a[i], f[a[i]] = 1;

  if (k == 1) return std::cout << 1 << "\n", void();
  
  std::sort(a + 1, a + k + 1);
  if (a[1] != 0) {
    for (int i = 0; i <= a[k]; i++) f[i] = f[i + a[1]];
  }
  
  int d = a[k] - a[1], m = n / 2;

  inv[1] = g[0] = 1;
  for (int i = 2; i <= d * m; i++) inv[i] = i64(mod - mod / i) * inv[mod % i];

  for (int i = 0; i < d * m; i++) {
    Z cur = 0;
    for (int j = 0; j <= std::min(i, d - 1); j++) {
      cur += (j + 1) * f[j + 1] * g[i - j];
    }
    cur *= m;
    for (int j = std::max(0, i - d); j < i; j++) {
      cur -= (j + 1) * g[j + 1] * f[i - j];
    }
    g[i + 1] = cur * inv[i + 1];
    ans += g[i + 1] * g[i + 1];
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
