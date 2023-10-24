/**
 * @file    AT_arc084_b [ARC084B] Small Multiple.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-08-04
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e6 + 50;
int k;
std::deque<std::pair<int, int>> dq;
bool vis[N];
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> k;
  dq.emplace_back(1, 1);
  while (!dq.empty()) {
    auto [num, val] = dq.front();
    dq.pop_front();
    if (num == 0) {
      std::cout << val << "\n";
      return 0;
    }
    if (!vis[10 * num % k]) 
      vis[10 * num % k] = true, dq.emplace_front(10 * num % k, val);
    if (!vis[num + 1])
      dq.emplace_back(num + 1, val + 1);
  }
  return 0;
}