/**
 * @file    P3551 [POI2013] USU-Take-out.cpp
 * @author  ForgotDream
 * @brief   Stack
 * @date    2023-11-28
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 1e6 + 50;
int n, k, s[N];
int st[N], top;
void solve() {
  std::cin >> n >> k;
  std::vector<std::vector<int>> ans;
  for (int i = 1; i <= n; i++) {
    char c;
    std::cin >> c;
    st[++top] = i, s[top] = s[top - 1] + (c == 'c');
    if (top >= k + 1 && s[top] - s[top - k - 1] == 1) {
      ans.emplace_back();
      for (int j = top - k; j <= top; j++) ans.back().push_back(st[j]);
      top = top - k - 1;
    }
  }
  std::sort(ans.begin(), ans.end());
  for (const auto &i : ans) {
    for (auto j : i) std::cout << j << " ";
    std::cout << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
