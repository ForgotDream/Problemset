/**
 * @file    P1429 平面最近点对（加强版）.cpp
 * @author  ForgotDream
 * @brief   Divide and Conquer
 * @date    2023-10-23
 */
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using i64 = long long;
using f80 = long double;
using pff = std::pair<f80, f80>;

constexpr int N = 2e5 + 50;
int n;
pff a[N];
inline f80 dis(int i, int j) {
  return hypot(a[i].first - a[j].first, a[i].second - a[j].second);
}
f80 solve(int l, int r) {
  f80 res = 1e18;
  if (l == r) return res;
  if (l == r - 1) return dis(l, r);
  int mid = (l + r) >> 1;
  res = std::min(solve(l, mid), solve(mid + 1, r));
  std::vector<int> tmp;
  for (int i = l; i <= r; i++) {
    if (fabs(a[mid].first - a[i].first) < res) tmp.push_back(i);
  }
  std::sort(tmp.begin(), tmp.end(),
            [&](int lhs, int rhs) { return a[lhs].second < a[rhs].second; });
  int k = tmp.size();
  for (int i = 0; i < k; i++) {
    for (int j = i + 1; j < k && a[tmp[j]].second - a[tmp[i]].second < res; j++) {
      f80 cur = dis(tmp[i], tmp[j]);
      res = std::min(res, cur);
    }
  }
  return res;
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i].first >> a[i].second;
  std::sort(a + 1, a + n + 1);
  std::cout << std::fixed << std::setprecision(4) << solve(1, n) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
