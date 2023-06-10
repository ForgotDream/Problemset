#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].first >> a[i].second;
  }

  std::sort(a.begin(), a.end(), [&](std::pair<int, int> lhs, std::pair<int, int> rhs) {
    if (lhs.first == rhs.first) {
      return lhs.second > rhs.second;
    }
    return lhs.first < rhs.first;
  });

  int cnt = 0, ans = 0, used = 0;
  bool flg = false;
  for (int i = 0; i < n; i++) {
    if (flg) {
      if (a[i].first == a[i - 1].first) {
        continue;
      } else {
        flg = false;
      }
    }

    if (a[i].first > cnt) {
      ans += a[i].second;
      cnt++, used++;

      std::cerr << a[i].second << " " << cnt << "\n";

      if (cnt == a[i].first) {
        cnt -= used, used = 0;
        flg = true;
      } else {
        cnt -= used - 1, used = 1;
      }
    }
  }
  std::cerr << "\n";

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