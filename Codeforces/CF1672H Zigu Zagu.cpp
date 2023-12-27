/*
 * @file    CF1672H Zigu Zagu.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-12-22
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 50;
int n, q, a[N], s[N][2];

void solve() {
  std::cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    char c;
    std::cin >> c, a[i] = c - '0';
    if (i == 1) continue;
    s[i][0] = s[i - 1][0] + (!a[i] && !a[i - 1]);
    s[i][1] = s[i - 1][1] + (a[i] && a[i - 1]);
  }

  for (int l, r; q; q--) {
    std::cin >> l >> r;
    std::cout << std::max(s[r][0] - s[l][0], s[r][1] - s[l][1]) + 1 << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // fin >> t;
  while (t--) solve();
  return 0;
}
