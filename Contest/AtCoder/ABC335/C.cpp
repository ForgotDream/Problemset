#include <bits/stdc++.h>

using i64 = long long;
using pii = std::pair<int, int>;

int n, q;
std::deque<pii> dq;

void solve() {
  std::cin >> n >> q;
  for (int i = 1; i <= n; i++) dq.emplace_back(i, 0);

  for (int i = 1, opt, u; i <= q; i++) {
    char c;
    std::cin >> opt;
    if (opt == 1) {
      std::cin >> c;
      auto [dx, dy] = dq.front();
      dq.pop_back();
      if (c == 'R') dx++;
      else if (c == 'L') dx--;
      else if (c == 'U') dy++;
      else dy--;
      dq.emplace_front(dx, dy);
    } else {
      std::cin >> u;
      auto [x, y] = dq[u - 1];
      std::cout << x << " " << y << "\n";
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
