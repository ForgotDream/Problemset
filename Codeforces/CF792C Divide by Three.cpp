/**
 * @file    CF792C Divide by Three.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-11-01
 */
#include <cstring>
#include <iostream>
#include <stack>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, f[N][3], p[N][3];
char s[N];
int trans(char c) { return c - '0'; }
void solve() {
  std::cin >> (s + 1), n = std::strlen(s + 1);
  if (n == 1) {
    if (trans(s[1]) % 3 == 0) std::cout << s[1] << "\n";
    else std::cout << -1 << "\n";
    return;
  }
  std::memset(f, 0x3f, sizeof(f)), f[1][0] = 1, f[1][trans(s[1]) % 3] = 0;
  for (int i = 2; i <= n; i++) {
    int u = trans(s[i]) % 3;
    for (int j = 0; j < 3; j++) {
      f[i][j] = f[i - 1][j] + 1, p[i][j] = j;
      if (s[i] == '0' && f[i - 1][j] == i - 1) continue;
      if (f[i][j] > f[i - 1][(j - u + 3) % 3]) {
        f[i][j] = f[i - 1][(j - u + 3) % 3];
        p[i][j] = (j - u + 3) % 3;
      }
    }
  }
  if (f[n][0] == n) {
    for (int i = 1; i <= n; i++) {
      if (s[i] == '0') {
        std::cout << 0 << "\n";
        return;
      }
    }
    std::cout << -1 << "\n";
    return;
  }
  int pre;
  std::stack<int> ans;
  for (int i = n, j = 0; i >= 2; i--, j = pre) {
    pre = p[i][j];
    if (f[i][j] == f[i - 1][pre]) ans.push(i);
  }
  if (trans(s[1]) % 3 == pre) ans.push(1);
  while (!ans.empty()) std::cout << s[ans.top()], ans.pop();
  std::cout << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
