#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    std::cin >> b[i];
  }

  auto calc = [](std::vector<int> a) {
    int n = a.size();
    if (n == 0) {
      return std::vector<std::pair<int, int>>();
    }
    std::vector<std::pair<int, int>> res;
    res.emplace_back(a[0], 1);
    for (int i = 1; i < n; i++) {
      if (a[i] == a[i - 1]) {
        res[res.size() - 1].second++;
      } else {
        res.emplace_back(a[i], 1);
      }
    }
    return res;
  };

  auto newa = calc(a), newb = calc(b);
  std::vector<int> ba(2 * n + 1), bb(2 * n + 1);
  for (auto i : newa) {
    ba[i.first] = std::max(ba[i.first], i.second);
  }
  for (auto i : newb) {
    bb[i.first] = std::max(bb[i.first], i.second);
  }

  int ans = 0;
  for (int i = 0; i <= 2 * n; i++) {
    ans = std::max(ans, ba[i] + bb[i]);
  }

  std::cout << ans << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}