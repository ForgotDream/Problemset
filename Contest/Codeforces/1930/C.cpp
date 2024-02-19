#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 3e5 + 50;

int n;

void solve() {
  std::cin >> n;
  std::priority_queue<int> pq;
  for (int i = 1, u; i <= n; i++) std::cin >> u, pq.push(u + i);

  int lst = 2e9;
  while (!pq.empty()) {
    int u = pq.top();
    pq.pop();
    if (u >= lst) u = lst - 1;
    lst = u;
    std::cout << u << " ";
  }
  std::cout << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
