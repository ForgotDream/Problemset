/*
 * @file    CF830D Singer House.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2024-01-10
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int mod = 1e9 + 7;

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
  ModInt(i64 v = 0) : val((v + MOD) % MOD) {}
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
  ModInt<MOD> operator-() { return ModInt<MOD>(MOD - val); }
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

constexpr int N = 405;

int n;
Z f[N], g[N], h[N];

void solve() {
  std::cin >> n;

  g[0] = 1;
  for (int i = 0; i < n; i++) {
    std::swap(f, g);
    std::fill(g, g + N, 0);
    for (int j = 0; i + j - 1 <= n; j++) {
      for (int k = 0; i + j + k - 1 <= n; k++) {
        if (f[j] != 0 && f[k] != 0) {
          auto v = f[j] * f[k];
          g[j + k + 1] += v;
          g[j + k] += v * (2 * (j + k) + 1);
          g[j + k - 1] += v * ((j + k) * (j + k) - (j + k));
        }
      }
    }
  }
  std::cout << g[1] << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
