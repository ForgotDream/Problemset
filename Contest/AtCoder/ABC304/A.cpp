#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<std::pair<int, std::string>> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].second >> a[i].first;
  }

  auto p = std::min_element(a.begin(), a.end());
  std::rotate(a.begin(), p, a.end());

  for (int i = 0; i < n; i++) {
    std::cout << a[i].second << "\n";
  }

  return 0;
}