/**
 * @file    P2949 Work Scheduling G.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-05-13
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].first >> a[i].second;
  }

  std::sort(a.begin(), a.end());

  std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
  i64 sum = 0;
  for (int i = 0; i < n; i++) {
    if (a[i].first <= pq.size()) {
      if (a[i].second > pq.top()) {
        sum -= pq.top();
        sum += a[i].second;
        pq.pop();
        pq.push(a[i].second);
      }
    } else {
      sum += a[i].second;
      pq.push(a[i].second);
    }
  }

  std::cout << sum << "\n";

  return 0;
}