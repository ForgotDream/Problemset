/**
 * @file    CF1411D Grime Zoo.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-08-31
 */
#include <cstring>
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50;
char s[N];
i64 x, y;
int n;
void calc1() {
  i64 sum = 0, ans = 0;
  int c0 = 0, c1 = 0, r0 = 0, r1 = 0;
  for (int i = 1; i <= n; i++) {
    if (s[i] == '0') c0++, sum += c1 * y;
    else c1++, sum += c0 * x;
  }
  ans = sum;
  for (int i = n; i >= 1; i--) {
    if (s[i] == '0') {
      c0--, r0++;
    } else if (s[i] == '1') {
      c1--, r1++;
    } else {
      c1--;
      sum = sum - c0 * x - r0 * y + c1 * y + r1 * x;
      ans = std::min(ans, sum);
      r0++;
    }
  }
  std::cout << ans << "\n";
}
void calc2() {
  i64 sum = 0, ans;
  int c0 = 0, c1 = 0, r0 = 0, r1 = 0;
  for (int i = 1; i <= n; i++) {
    if (s[i] == '1') c1++, sum += c0 * x;
    else c0++, sum += c1 * y;
  }
  ans = sum;
  for (int i = n; i >= 1; i--) {
    if (s[i] == '0') {
      c0--, r0++;
    } else if (s[i] == '1') {
      c1--, r1++;
    } else {
      c0--;
      sum = sum - c1 * y - r1 * x + c0 * x + r0 * y;
      ans = std::min(ans, sum);
      r1++;
    }
  }
  std::cout << ans << "\n";
}
void solve() {
  std::cin >> (s + 1) >> x >> y;
  n = std::strlen(s + 1);
  if (x > y) calc1();
  else calc2();
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}