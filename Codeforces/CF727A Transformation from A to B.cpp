/**
 * @file    CF727A Transformation: from A to B.cpp
 * @author  ForgotDream
 * @brief   DFS
 * @date    2023-08-29
 */
#include <iostream>

using i64 = long long;

constexpr int N = 50;
int a, b;
int s[N];
void dfs(i64 cur, int cnt) {
  if (cur > b) return;
  if (cur == b) {
    std::cout << "YES\n";
    std::cout << cnt << "\n";
    i64 tmp = a;
    for (int i = 1; i <= cnt; i++) {
      std::cout << tmp << " ";
      if (s[i] == 1) tmp *= 2;
      else tmp = 10 * tmp + 1;
    }
    std::cout << "\n";
    exit(0);
  }
  s[cnt] = 1, dfs(2 * cur, cnt + 1), s[cnt] = 0;
  s[cnt] = 2, dfs(10 * cur + 1, cnt + 1), s[cnt] = 0;
}
void solve() {
  std::cin >> a >> b;
  dfs(a, 1);
  std::cout << "NO\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}