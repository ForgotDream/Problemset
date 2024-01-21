#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 50;

int rt, n, nxt[N];

void solve() {
  std::cin >> n;
  for (int i = 1, p; i <= n; i++) {
    std::cin >> p;
    if (p == -1) rt = i;
    else nxt[p] = i;
  }

  while (rt) std::cout << rt << " ", rt = nxt[rt];
  std::cout << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
