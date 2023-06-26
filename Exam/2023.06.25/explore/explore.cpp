#include <bits/stdc++.h>

using i64 = long long;

int main() {
  freopen("explore.in", "r", stdin);
  freopen("explore.out", "w", stdout);

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> a;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int x, y;
    std::cin >> x >> y;
    if (x + y >= n) {
      ans++;
    } else {
      a.emplace_back(x, y);
    }
  }

  auto cmp = [&](std::pair<int, int> lhs, std::pair<int, int> rhs) {
    if (lhs.first == rhs.first) {
      return lhs.second > rhs.second;
    }
    return lhs.first < rhs.first;
  };
  std::sort(a.begin(), a.end(), cmp);

  int m = a.size();
  std::vector<int> f(n);
  f[0] = 1;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < i; j++) {
      if (a[i].first == a[j].first) {
        continue;
      }
      if (a[i].second >= a[j].second) {
        continue;
      }
      f[i] = std::max(f[i], f[j] + 1);
    }
  }

  int max = *std::max_element(f.begin(), f.end());
  std::cout << ans + m - max << "\n";

  return 0;
}