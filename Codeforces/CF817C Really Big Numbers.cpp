/**
 * @file    CF817C Really Big Numbers.cpp
 * @author  ForgotDream
 * @brief   Binary Search
 * @date    2023-10-31
 */
#include <iostream>

using i64 = long long;

i64 n, s;
bool check(i64 num) {
  i64 sum = 0, cpy = num;
  while (cpy) sum += cpy % 10, cpy /= 10;
  return num - sum >= s;
}
void solve() {
  std::cin >> n >> s;
  i64 l = 0, r = n, ans = n + 1;
  while (l <= r) {
    i64 mid = (l + r) >> 1;
    if (check(mid)) r = mid - 1, ans = mid;
    else l = mid + 1;
  }
  std::cout << n - ans + 1 << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
