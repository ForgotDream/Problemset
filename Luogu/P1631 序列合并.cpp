/**
 * @file    P1631 序列合并.cpp
 * @author  ForgotDream
 * @brief   Heap
 * @date    2023-05-05
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    std::cin >> b[i];
  }

  std::priority_queue<
    std::pair<int, int>,
    std::vector<std::pair<int, int>>,
    std::greater<std::pair<int, int>>
  > pq;
  std::vector<int> p(n);
  for (int i = 0; i < n; i++) {
    pq.push(std::make_pair(a[i] + b[0], i));
  }

  int cnt = 0;
  while (cnt < n) {
    std::cout << pq.top().first << " ";
    int i = pq.top().second;
    pq.pop();
    pq.push(std::make_pair(a[i] + b[++p[i]], i));
    cnt++;
  }
  std::cout << "\n";

  return 0;
}