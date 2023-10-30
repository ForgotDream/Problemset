/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-10-30
 */
#include <iostream>

using i64 = long long;

constexpr int N = 5e5 + 50, mod = 998244353;
struct SegTree {
  struct Node {
    int lc, rc;
    friend Node operator+(const Node &lhs, const Node &rhs) {
      Node res;
      return res;
    }
  } tree[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
} seg;
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void solve() {
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
