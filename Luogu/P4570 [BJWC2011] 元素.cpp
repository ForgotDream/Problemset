/**
 * @file    P4570 [BJWC2011] 元素.cpp
 * @author  ForgotDream
 * @brief   Linear Basis
 * @date    2023-08-27
 */
#include <algorithm>
#include <iostream>

using i64 = long long;
using u64 = unsigned long long;

namespace VECSPACE {
constexpr int N = 64;
u64 p[N];
bool insert(u64 val) {
  for (int i = 63; i >= 0; i--) {
    if (!(val & (1ll << i))) continue;
    if (!p[i]) {
      p[i] = val;
      break;
    }
    val ^= p[i];
  }
  return val == 0;
}
}
constexpr int N = 1050;
struct Node {
  i64 num, val;
  bool operator<(const Node &rhs) const { return val > rhs.val; }
} a[N];
int n;
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i].num >> a[i].val;
  std::sort(a + 1, a + n + 1);
  i64 ans = 0, sum = 0;
  for (int i = 1; i <= n; i++) {
    auto [num, val] = a[i];
    if (VECSPACE::insert(num)) ans += val;
    sum += val;
  }
  std::cout << sum - ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}