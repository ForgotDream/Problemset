#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;

  std::vector<int> red(n + 1), yellow(n + 1);
  while (q--) {
    int opt, x;
    std::cin >> opt >> x;
    if (opt == 1) {
      yellow[x]++;
    } else if (opt == 2) {
      red[x]++;
    } else {
      if (red[x] || yellow[x] >= 2) {
        std::cout << "Yes" << "\n";
      } else {
        std::cout << "No" << "\n";
      }
    }
  }

  return 0;
}