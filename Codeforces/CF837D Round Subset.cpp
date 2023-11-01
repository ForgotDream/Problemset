/**
 * @file    CF837D Round Subset.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-10-31
 */
#include <cstring>
#include <iostream>

using i64 = long long;

// 挺妙的
constexpr int N = 205, M = 60;
int n, k, f[2][N][M * N];
i64 a[N];
inline int calc(i64 num, int p) {
  int res = 0;
  while (num && num % p == 0) num /= p, res++;
  return res;
}
void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  int sum = 0, cur = 0, pre = 1;
  std::memset(f, -1, sizeof(f)), f[cur][0][0] = 0;
  for (int i = 1; i <= n; i++) {
    std::swap(cur, pre);
    int cnt2 = calc(a[i], 2), cnt5 = calc(a[i], 5);
    sum += cnt2;
    for (int j = 0; j <= std::min(i, k); j++) {
      for (int k = 0; k <= sum; k++) {
        f[cur][j][k] = f[pre][j][k];
        if (k >= cnt2 && j && f[pre][j - 1][k - cnt2] != -1) {
          f[cur][j][k] = std::max(f[cur][j][k], f[pre][j - 1][k - cnt2] + cnt5);
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; i <= sum; i++) {
    ans = std::max(ans, std::min(i, f[cur][k][i]));
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
