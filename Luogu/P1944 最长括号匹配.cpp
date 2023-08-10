/**
 * @file    P1944 最长括号匹配.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-09
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e6 + 50;
int f[N], n;
std::string s;
int ans, pivot;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> s;
  n = s.length(), s = " " + s;
  for (int i = 1; i <= n; i++) {
    if (s[i] == '(' || s[i] == '[') continue;
    else if ((s[i] == ')' && s[i - f[i - 1] - 1] == '(') ||
             (s[i] == ']' && s[i - f[i - 1] - 1] == '[')) {
      f[i] = f[i - 1] + f[i - f[i - 1] - 2] + 2;
      if (f[i] > ans) ans = f[i], pivot = i;
    }
  }
  for (int i = pivot - ans + 1; i <= pivot; i++) std::cout << s[i];
  std::cout << "\n";
  return 0;
}