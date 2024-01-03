#include <bits/stdc++.h>

using i64 = long long;

const std::vector<int> &foo(const std::vector<int> &a) {
  return a;
}

void solve() {
  for (auto i : foo(std::vector<int>{1, 2, 3, 4, 5})) {
    std::cout << i << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
