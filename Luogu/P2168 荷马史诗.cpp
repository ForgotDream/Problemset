/**
 * @file    P2168 荷马史诗.cpp
 * @author  ForgotDream
 * @brief   Huffman Tree + Heap
 * @date    2023-05-06
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  std::priority_queue<
    std::pair<i64, int>,
    std::vector<std::pair<i64, int>>,
    std::greater<std::pair<i64, int>>
  > pq;
  for (int i = 0; i < n; i++) {
    i64 w;
    std::cin >> w;
    pq.emplace(w, 0);
  }

  while ((pq.size() - 1) % (k - 1) != 0) {
    pq.emplace(0, 0);
  }

  i64 ans = 0;
  while (pq.size() >= k) {
    int maxDep = -1;
    i64 cnt = 0;
    for (int i = 0; i < k; i++) {
      maxDep = std::max(pq.top().second, maxDep);
      cnt += pq.top().first;
      pq.pop();
    }
    ans += cnt;
    pq.emplace(cnt, maxDep + 1);
  }

  std::cout << ans << "\n";
  std::cout << pq.top().second << "\n";

  return 0;
}