/**
 * @file    P2216 理想的正方形.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-18
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int a, b, n;
  std::cin >> a >> b >> n;

  std::vector m(a, std::vector<int>(b));
  decltype(m) max(m), min(m);
  for (int i = 0; i < a; i++) {
    for (int j = 0; j < b; j++) { std::cin >> m[i][j]; }
  }

  // initialize.
  for (int j = 0; j < b; j++) {
    std::deque<int> cmax, cmin;
    max[0][j] = min[0][j] = m[0][j];
    cmax.push_back(0), cmin.push_back(0);
    for (int i = 1; i < a; i++) {
      while (!cmax.empty() && cmax.front() <= i - n) { cmax.pop_front(); }
      while (!cmin.empty() && cmin.front() <= i - n) { cmin.pop_front(); }
      max[i][j] = std::max(m[cmax.front()][j], m[i][j]);
      min[i][j] = std::min(m[cmin.front()][j], m[i][j]);
      while (!cmax.empty() && m[cmax.back()][j] < m[i][j]) { cmax.pop_back(); }
      while (!cmin.empty() && m[cmin.back()][j] > m[i][j]) { cmin.pop_back(); }
      cmax.push_back(i), cmin.push_back(i);
    }
  }

  int ans = inf;
  for (int i = n - 1; i < a; i++) {
    std::deque<int> cmax, cmin;
    cmax.push_back(0), cmin.push_back(0);
    for (int j = 1; j < n; j++) {
      while (!cmax.empty() && max[i][cmax.back()] < max[i][j]) { cmax.pop_back(); }
      while (!cmin.empty() && min[i][cmin.back()] > min[i][j]) { cmin.pop_back(); }
      cmax.push_back(j), cmin.push_back(j);
    }
    ans = std::min(ans, max[i][cmax.front()] - min[i][cmin.front()]);
    for (int j = n; j < b; j++) {
      while (!cmax.empty() && max[i][cmax.back()] < max[i][j]) { cmax.pop_back(); }
      while (!cmin.empty() && min[i][cmin.back()] > min[i][j]) { cmin.pop_back(); }
      cmax.push_back(j), cmin.push_back(j);
      while (!cmax.empty() && cmax.front() <= j - n) { cmax.pop_front(); }
      while (!cmin.empty() && cmin.front() <= j - n) { cmin.pop_front(); }
      ans = std::min(ans, max[i][cmax.front()] - min[i][cmin.front()]);
    }
  }

  std::cout << ans << "\n";

  return 0;
}