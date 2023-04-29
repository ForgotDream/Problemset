#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, t;
  std::cin >> n >> t;

  std::vector<int> c(n);
  std::unordered_map<int, int> mp, no;
  for (int i = 0; i < n; i++) {
    std::cin >> c[i];
    mp[c[i]] = 0;
  }
  for (int i = 0; i < n; i++) {
    int r;
    std::cin >> r;
    if (mp[c[i]] < r) {
      mp[c[i]] = r;
      no[c[i]] = i + 1;
    }
  }

  if (mp.count(t)) {
    std::cout << no[t] << "\n";
  } else {
    std::cout << no[c[0]] << "\n";
  }

  return 0;
}