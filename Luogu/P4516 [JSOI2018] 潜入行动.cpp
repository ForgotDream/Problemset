/*
 * @file    P4516 [JSOI2018] 潜入行动.cpp
 * @author  ForgotDream
 * @brief   DP on Tree
 * @date    2024-01-04
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50, K = 105, mod = 1e9 + 7;

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
  int val;
  explicit operator int() { return val; }
  ModInt(int v = 0) : val(v % MOD) {}
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
    val = 1ll * val * rhs.val % MOD;
    return *this;
  }
  ModInt<MOD> &operator/=(const ModInt<MOD> &rhs) {
    val = 1ll * val * getInv(rhs.val) % MOD;
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
    return ModInt<MOD>(1ll * lhs.val * rhs.val % MOD);
  }
  friend ModInt<MOD> operator/(const ModInt<MOD> &lhs, const ModInt<MOD> &rhs) {
    return ModInt<MOD>(1ll * lhs.val * getInv(rhs.val) % MOD);
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

int n, k;
std::vector<int> adj[N];

Z f[N][K][2][2], g[K][2][2];
int siz[N];

void dfs(int u, int frm) {
  siz[u] = 1, f[u][1][1][0] = f[u][0][0][0] = 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
    for (int i = 0; i <= std::min(siz[u], k); i++) {
      for (int j = 0; j < 2; j++) {
        for (int l = 0; l < 2; l++) {
          g[i][j][l] = f[u][i][j][l];
          f[u][i][j][l] = 0;
        }
      }
    }
    for (int i = 0; i <= std::min(siz[u], k); i++) {
      for (int j = 0; j <= std::min(siz[v], k - i); j++) {
        f[u][i + j][0][0] += f[v][j][0][1] * g[i][0][0];

        f[u][i + j][0][1] += (f[v][j][0][1] + f[v][j][1][1]) * g[i][0][1];
        f[u][i + j][0][1] += f[v][j][1][1] * g[i][0][0];

        f[u][i + j][1][0] += (f[v][j][0][0] + f[v][j][0][1]) * g[i][1][0];

        f[u][i + j][1][1] += (f[v][j][1][0] + f[v][j][1][1]) * g[i][1][0];
        f[u][i + j][1][1] += (f[v][j][0][0] + f[v][j][0][1] + f[v][j][1][0] + f[v][j][1][1]) * g[i][1][1];
      }
    }
    siz[u] += siz[v];
  }
}

void solve() {
  std::cin >> n >> k;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  dfs(1, 0);
  std::cout << f[1][k][1][1] + f[1][k][0][1] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
