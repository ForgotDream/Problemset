/**
 * @file    P2085 最小函数值.cpp
 * @author  ForgotDream
 * @brief   Heap
 * @date    2023-05-06
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::priority_queue<
    std::pair<i64, int>, 
    std::vector<std::pair<i64, int>>,
    std::greater<std::pair<i64, int>>
  > pq;
  std::vector<std::tuple<i64, i64, i64>> f;
  std::vector<int> p(n, 1);

  for (int i = 0; i < n; i++) {
    i64 a, b, c;
    std::cin >> a >> b >> c;
    f.emplace_back(a, b, c);
    pq.emplace(a + b + c, i);
  }

  for (int i = 0; i < m; i++) {
    std::cout << pq.top().first << " \n"[i == m - 1];
    int pivot = pq.top().second;
    pq.pop();
    ++p[pivot];
    i64 a = std::get<0>(f[pivot]), b = std::get<1>(f[pivot]), c = std::get<2>(f[pivot]);
    pq.emplace(a * p[pivot] * p[pivot] + b * p[pivot] + c, pivot);
  }

  return 0;
}