/**
 * @file    CF1613A Long Comparison.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-08-21
 */
#include <cassert>
#include <iostream>

using i64 = long long;

int t;
int x1, p1, x2, p2;

int len(int num) {
  int res = 0;
  while (num) num /= 10, res++;
  return res;
}

void solve() {
  std::cin >> x1 >> p1 >> x2 >> p2;
  int l1 = len(x1), l2 = len(x2);
  if (l1 + p1 != l2 + p2) {
    if (l1 + p1 > l2 + p2) std::cout << ">\n";
    else std::cout << "<\n";
    return;
  }
  while (len(x1) != len(x2)) {
    if (x1 < x2) x1 *= 10;
    else x2 *= 10;
  }
  assert(len(x1) == len(x2));
  if (x1 > x2) std::cout << ">\n";
  else if (x1 < x2) std::cout << "<\n";
  else std::cout << "=\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> t;

  while (t--) solve();

  return 0;
}