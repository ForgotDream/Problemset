#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::map<int, int> mp;
  for (int i = 0; i < n; i++) {
    mp[a[i]]++;
  }

  int ans = 0;
  for (auto i : mp) {
    ans += i.second / 2;
  }

  std::cout << ans << "\n";

  return 0;
}