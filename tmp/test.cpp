#include <bits/stdc++.h>

void solve() {
  std::set<int> s = {1, 2, 3, 4, 5};

  auto it1 = --s.end();
  auto it2 = s.rbegin().base();
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
