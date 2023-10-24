/**
 * @file    P2308 添加括号.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-09
 */
#include <bits/stdc++.h>
using i64 = long long;
using pii = std::pair<int, int>;
constexpr int N = 25;
int n, a[N], f[N][N], s[N];
std::queue<int> q;
void print(int l, int r) {
  if (l == r) return void(std::cout << a[l]);
  std::cout << "(";
  for (int k = l; k < r; k++) {
    if (f[l][r] == f[l][k] + f[k + 1][r] + s[r] - s[l - 1]) {
      print(l, k), std::cout << "+", print(k + 1, r);
      q.push(s[r] - s[l - 1]);
      break;
    }
  }
  std::cout << ")";
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], s[i] = s[i - 1] + a[i];
  memset(f, 0x3f, sizeof(f));
  for (int i = 1; i <= n; i++) f[i][i] = 0;
  for (int len = 2; len <= n; len++) {
    for (int l = 1; l + len - 1 <= n; l++) {
      int r = l + len - 1;
      for (int k = l; k < r; k++) {
        f[l][r] = std::min(f[l][r], f[l][k] + f[k + 1][r] + s[r] - s[l - 1]);
      }
    }
  }
  print(1, n);
  std::cout << "\n" << f[1][n] << "\n";
  while (!q.empty()) std::cout << q.front() << " ", q.pop();
  std::cout << "\n";
  return 0;
}