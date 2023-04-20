/**
 * @file    LOJ#10005 数列极差.cpp
 * @author  ForgotDream
 * @brief   贪心
 * @date    2023-03-20
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  int tmp;
  std::cin >> tmp;

  std::priority_queue<int> pq;
  for (int i = 0; i < n; i++) {
    pq.push(a[i]);
  }

  while (pq.size() > 1) {
    int x = pq.top();
    pq.pop();
    int y = pq.top();
    pq.pop();
    pq.push(x * y + 1);
  }

  int s1 = pq.top();
  pq.pop();

  for (int i = 0; i < n; i++) {
    pq.push(-1 * a[i]);
  }

  while (pq.size() > 1) {
    int x = pq.top();
    pq.pop();
    int y = pq.top();
    pq.pop();
    pq.push(-1 * (x * y + 1));
  }

  int s2 = -1 * pq.top();
  std::cout << s2 - s1 << "\n";

  return 0;
}