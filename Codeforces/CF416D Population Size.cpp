/**
 * @file    CF416D Population Size.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-09-04
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using i64 = long long;

const int N = 2e5 + 5;
i64 n, val[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> val[i];
  i64 ans = 0, i = 1;
  while (i <= n) {
    ans++;
    i64 x = 0, y = 0;
    for (int j = i; j <= n; j++)
      if (~val[j]) {
        if (!x) {
          x = j;
        } else {
          y = j;
          break;
        }
      }
    if (!y) break;
    if ((val[y] - val[x]) % (y - x) != 0) {
      i = y;
      continue;
    }
    i64 delta = (val[y] - val[x]) / (y - x);
    if (val[x] - (x - i) * delta <= 0) {
      i = y;
      continue;
    }
    for (i = y; i <= n; i++) {
      if (val[i] + delta <= 0) break;
      if (~val[i + 1] && val[i] + delta != val[i + 1]) break;
      val[i + 1] = val[i] + delta;
    }
    i++;
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}