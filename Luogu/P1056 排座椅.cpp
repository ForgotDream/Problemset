/**
 * @file    P1056 排座椅.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-05-13
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int m, n, k, l, d;
  std::cin >> m >> n >> k >> l >> d;

  std::vector<std::pair<int, int>> bx(m), by(n);
  for (int i = 0; i < m; i++) {
    bx[i].second = i;
  }
  for (int i = 0; i < n; i++) {
    by[i].second = i;
  }

  for (int i = 0; i < d; i++) {
    int x1, x2, y1, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    if (x1 == x2) {
      by[std::min(y1, y2)].first++;
    } else {
      bx[std::min(x1, x2)].first++;
    }
  }

  auto cmp = 
  [](const std::pair<int, int> &lhs, const std::pair<int, int> &rhs) {
    if (lhs.first == rhs.first) {
      return lhs.second < rhs.second;
    }
    return lhs.first > rhs.first;
  };

  std::sort(bx.begin() + 1, bx.end(), cmp);
  std::sort(by.begin() + 1, by.end(), cmp);

  std::vector<int> ans;
  for (int i = 1; i <= k; i++) {
    ans.push_back(bx[i].second);
  }
  std::sort(ans.begin(), ans.end());
  for (int i = 0; i < k; i++) {
    std::cout << ans[i] << " \n"[i == k - 1];
  }

  ans.clear();
  for (int i = 1; i <= l; i++) {
    ans.push_back(by[i].second);
  }
  std::sort(ans.begin(), ans.end());
  for (int i = 0; i < l; i++) {
    std::cout << ans[i] << " \n"[i == l - 1];
  }

  return 0;
}