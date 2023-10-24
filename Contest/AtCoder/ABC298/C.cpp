#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, q;
  std::cin >> n >> q;

  std::vector<std::multiset<int>> a(n + 1);
  std::vector<std::set<int>> b(static_cast<int>(2e5 + 50));

  while (q--) {
    int opt;
    std::cin >> opt;
    if (opt == 1) {
      int x, y;
      std::cin >> x >> y;
      a[y].insert(x);
      b[x].insert(y);
    } else if (opt == 2) {
      int x;
      std::cin >> x;
      for (auto it = a[x].begin(); it != a[x].end(); it++) {
        std::cout << *it << " ";
      }
      std::cout << "\n";
    } else {
      int x;
      std::cin >> x;
      for (auto it = b[x].begin(); it != b[x].end(); it++) {
        std::cout << *it << " ";
      }
      std::cout << "\n";
    }
  }

  return 0;
}