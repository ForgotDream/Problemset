/**
 * @file    CF351B Jeff and Furik.cpp
 * @author  ForgotDream
 * @brief   Fenwick
 * @date    2023-08-21
 */
#include <iomanip>
#include <iostream>

using i64 = long long;

template<int N = 3050>
struct BIT {
  int tree[N];
  void add(int pos, int val) {
    for (int i = pos; i < N; i += (i & -i)) tree[i] += val;
  }
  int query(int pos) {
    int res = 0;
    for (int i = pos; i; i -= (i & -i)) res += tree[i];
    return res;
  }
};
BIT bit;
constexpr int N = 3050;
int n, a[N], ans;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(6);

  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    ans += bit.query(n) - bit.query(a[i]);
    bit.add(a[i], 1);
  }

  std::cout << 1. * (2 * ans - ans % 2) << "\n";

  return 0;
}