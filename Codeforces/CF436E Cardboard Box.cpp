/**
 * @file    CF436E Cardboard Box.cpp
 * @author  ForgotDream
 * @brief   反悔贪心
 * @date    2023-08-29
 */
#include <iostream>
#include <queue>

using i64 = long long;
using pli = std::pair<i64, int>;

constexpr int N = 3e5 + 50;
int n, p, ans[N];
i64 cost, a[2 * N];
bool vis[2 * N];
std::priority_queue<pli, std::vector<pli>, std::greater<pli>> q1, q2;
void shrink(std::priority_queue<pli, std::vector<pli>, std::greater<pli>> &q) {
  while (!q.empty() && vis[q.top().second]) q.pop();
}
void solve() {
  std::cin >> n >> p;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i] >> a[i + n];
    a[i + n] -= a[i];
    q1.emplace(a[i], i), q2.emplace(a[i + n] + a[i], i);
  }
  for (int i = 1; i <= p; i++) {
    shrink(q1), shrink(q2);
    int u = q1.top().second;
    q1.pop(), shrink(q1);
    if (i != p && !q2.empty() && a[u] + q1.top().first >= q2.top().first) {
      q1.emplace(a[u], u);
      u = q2.top().second, q2.pop();
    }
    if (u <= n) q1.emplace(a[u + n], u + n);
    cost += a[u], ans[u - (u > n ? n : 0)]++, vis[u] = true;
  }
  std::cout << cost << "\n";
  for (int i = 1; i <= n; i++) std::cout << ans[i];
  std::cout << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}