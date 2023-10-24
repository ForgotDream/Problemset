/**
 * @file    SP1553 BACKUP - Backup Files.cpp
 * @author  ForgotDream
 * @brief   反悔贪心
 * @date    2023-05-06
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    int n, k;
    std::cin >> n >> k;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;
    std::vector<int> a(n), d(n + 1);
    std::vector<int> l(n + 1), r(n + 1);
    std::cin >> a[0];
    for (int i = 1; i < n; i++) {
      std::cin >> a[i];
      d[i] = a[i] - a[i - 1];
      l[i] = i - 1, r[i] = i + 1;
      pq.emplace(d[i], i);
    }

    d[0] = d[n] = 0x3f3f3f3f;

    std::vector<bool> used(n + 1);
    int ans = 0;
    for (int i = 0; i < k; i++) {
      while (!pq.empty() && used[pq.top().second]) {
        pq.pop();
      }
      int id = pq.top().second, w = pq.top().first;
      pq.pop();
      ans += w;
      used[l[id]] = used[r[id]] = true;
      d[id] = d[l[id]] + d[r[id]] - d[id];
      pq.emplace(d[id], id);
      // l[r[id]] = l[id], r[l[id]] = r[id];
      l[id] = l[l[id]], r[id] = r[r[id]];
      r[l[id]] = id, l[r[id]] = id;
    }

    std::cout << ans << "\n";
  }

  return 0;
}