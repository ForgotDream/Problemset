/**
 * @file    P3467 PLA-Postering.cpp
 * @author  ForgotDream
 * @brief   Monotone Stack
 * @date    2023-05-26
 */
#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::stack<int> s;
  int ans = n;
  for (int i = 0; i < n; i++) {
    int d, w;
    std::cin >> d >> w;
    while (!s.empty() && s.top() >= w) {
      if (s.top() == w) {
        ans--;
      }
      s.pop();
    }
    s.push(w);
  }

  std::cout << ans << "\n";

  return 0;
}