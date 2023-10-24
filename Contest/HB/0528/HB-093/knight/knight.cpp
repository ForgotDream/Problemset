#include <bits/stdc++.h>

using i64 = long long;

int main() {
  freopen("knight.in", "r", stdin);
  freopen("knight.out", "w", stdout);

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].first >> a[i].second;
  }

  if (k == n) {
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
      ans += 2ll * (a[i].first + a[i].second);
    }
    std::cout << ans << "\n";
    return 0;
  } else if (k == 1) {
    int maxx = INT_MIN, maxy = INT_MIN;
    int minx = INT_MAX, miny = INT_MAX;
    for (int i = 0; i < n; i++) {
      maxx = std::max(maxx, a[i].first);
      maxy = std::max(maxy, a[i].second);
      minx = std::min(minx, a[i].first);
      miny = std::min(miny, a[i].second);
    }
    i64 ans = 2 * (maxx - minx) + 2 * (maxy - miny);
    std::cout << ans + 2ll * std::min({
      std::abs(maxx) + std::abs(maxy), 
      std::abs(minx) + std::abs(miny),
      std::abs(maxx) + std::abs(miny),
      std::abs(minx) + std::abs(maxy),
    }) << "\n";
    return 0;
  }

  return 0;
}