/**
 * @file    CF13C Sequence.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-10-28
 */
#include <iostream>
#include <queue>

using i64 = long long;

constexpr int N = 5050;
int n;
i64 ans;
std::priority_queue<int> pq;
void solve() {
  std::cin >> n;
  for (int i = 1, u; i <= n; i++) {
    std::cin >> u;
    pq.emplace(u);
    if (u < pq.top()) {
      ans += pq.top() - u;
      pq.pop(), pq.emplace(u);
    }
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
