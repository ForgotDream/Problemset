/**
 * @file    P3648 [APIO2014] 序列分割.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-07-27
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50, K = 205;
int n, k;
i64 f[K][N], a[N];

void solve(int l, int r, int s, int t, int k) {
  if (l > r) return;
  int mid = (l + r) >> 1, pivot = s;
  i64 ans = 0;
  for (int i = s; i <= std::min(t, mid); i++) {
    auto tmp = f[k - 1][i - 1] + a[i - 1] * (a[mid] - a[i - 1]);
    if (ans < tmp) ans = tmp, pivot = i;
  }
  f[k][mid] = ans;
  solve(l, mid - 1, s, pivot, k), solve(mid + 1, r, pivot, t, k);
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i], a[i] += a[i - 1];

  for (int i = 1; i <= k; i++) solve(1, n, 1, n, i);
  std::cout << f[k][n] << "\n";

  std::vector<int> ans;
  for (int i = k, pivot = n; i >= 1; i--) {
    for (int j = pivot - 1; j >= 1; j--) {
      if (f[i][pivot] == f[i - 1][j] + a[j] * (a[pivot] - a[j])) {
        pivot = j;
        ans.push_back(pivot);
        break;
      }
    }
  }
  std::sort(ans.begin(), ans.end());
  for (auto i : ans) std::cout << i << " ";
  std::cout << "\n";

  return 0;
}