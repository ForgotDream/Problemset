#include <bits/stdc++.h>

using i64 = long long;

int main() {
  freopen("card.in", "r", stdin);
  freopen("card.out", "w", stdout);

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> a(n);
  std::vector<int> b;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].first >> a[i].second;
  }

  std::sort(a.begin(), a.end());
  a.erase(std::unique(a.begin(), a.end()), a.end());

  for (int i = 0; i < a.size(); i++) {
    b.push_back(a[i].first);
  }

  std::sort(b.begin(), b.end());

  b.erase(std::unique(b.begin(), b.end()), b.end());

  std::vector<int> bucket(b.size());
  for (int i = 0; i < a.size(); i++) {
    int u = std::lower_bound(b.begin(), b.end(), a[i].first) - b.begin();
    bucket[u]++;
  }

  std::cout << n - *std::max_element(bucket.begin(), bucket.end()) << "\n";

  return 0;
}