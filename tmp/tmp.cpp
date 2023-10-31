/**
 * @file
 * @author  ForgotDream
 * @brief
 * @date    2023-10-30
 */
#include <algorithm>
#include <iostream>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2050;
int n, s, a[N], bln[N];
pii p[N];
void solve() {
  std::cin >> n >> s;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
