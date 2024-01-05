/*
 * @file    P6630 [ZJOI2020] 传统艺能.cpp
 * @author  ForgotDream
 * @brief   Matrix + Segment Tree + DP
 * @date    2024-01-05
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50, mod = 998244353;

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

int n, k;
Z inv2, invn;

struct Mat {
  Z a[4][4];
  Mat() { memset(a, 0, sizeof(a)); }
  Z *operator[](size_t idx) { return a[idx]; }
  const Z *operator[](size_t idx) const { return a[idx]; }
  friend Mat operator*(const Mat &lhs, const Mat &rhs) {
    Mat res;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 4; k++) {
          res[i][j] += lhs[i][k] * rhs[k][j];
        }
      }
    }
    return res;
  }
  static Mat eye() {
    Mat res;
    for (int i = 0; i < 4; i++) res[i][i] = 1;
    return res;
  }
};
Mat fastPow(Mat base, i64 exp) {
  Mat res = Mat::eye();
  for (; exp; exp >>= 1) {
    if (exp & 1) res = res * base;
    base = base * base;
  }
  return res;
}

struct Node {
  Z a = 0, b = 0, c = 0;
  Node(Z l, Z r) {
    a = (l * (l - 1) + (n - r + 1) * (n - r)) * inv2 * invn;
    b = l * (n - r + 1) * invn;
    c = 1 - a - b;
  }
  Node(Z a, Z b, Z c) : a(a), b(b), c(c) {}
};

Z ans;
void solve(int l, int r, const Node &lst) {
  Mat mat;
  Node cur(l, r);

  Z A = lst.a, B = lst.b, C = cur.a - lst.a, D = cur.b - lst.b, 
    E = 1 - A - B - C - D;

  mat[0][0] = A + C + E, mat[0][1] = D,         mat[0][2] = B,         mat[0][3] = 0;
  mat[1][0] = E,         mat[1][1] = A + C + D, mat[1][2] = 0,         mat[1][3] = B;
  mat[2][0] = E,         mat[2][1] = C + D,     mat[2][2] = A + B,     mat[2][3] = 0;
  mat[3][0] = E,         mat[3][1] = C + D,     mat[3][2] = 0,         mat[3][3] = A + B;

  mat = fastPow(mat, k);
  ans += mat[0][1] + mat[0][3];
  
  if (l == r) return;
  int mid;
  std::cin >> mid, solve(l, mid, cur), solve(mid + 1, r, cur);
}

void solve() {
  std::cin >> n >> k;
  inv2 = Z::getInv(2), invn = Z::getInv(1ll * n * (n + 1) / 2 % mod);
  solve(1, n, Node(0, 0, 1));
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
