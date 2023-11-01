/**
 * @file    CF846C Four Segments.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-11-01
 */
#include <cstring>
#include <iostream>

using i64 = long long;

constexpr int N = 5050;
int n, a[N];
i64 s[N], f[N][3];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], s[i] = s[i - 1] + a[i];
  std::memset(f, -0x3f, sizeof(f));
  for (int i = 0; i <= n; i++) f[i][0] = s[i];
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      f[i][1] = std::max(f[i][1], f[j][0] - s[i] + s[j]);
      f[i][2] = std::max(f[i][2], f[j][1] + s[i] - s[j]);
    }
  }
  i64 ans = -1e18;
  int p[3] = {0, 0, 0};
  for (int i = 0; i <= n; i++) {
    if (f[i][2] - s[n] + s[i] > ans) {
      ans = f[i][2] - s[n] + s[i];
      p[2] = i;
    }
  }
  for (int i = 0; i <= p[2]; i++) {
    if (f[p[2]][2] == f[i][1] + s[p[2]] - s[i]) {
      p[1] = i;
      break;
    }
  }
  for (int i = 0; i <= p[1]; i++) {
    if (f[p[1]][1] == f[i][0] - s[p[1]] + s[i]) {
      p[0] = i;
      break;
    }
  }
  std::cout << p[0] << " " << p[1] << " " << p[2] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
