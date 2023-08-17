#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::cin >> n;

  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }

  std::vector<int> s(1, 0);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    while (s.size() != 1 && a[s[s.size() - 1]] >= a[i]) {
      s.pop_back();
    }
    s.push_back(i);
    for (int j = 1; j <= s.size() - 1; j++) {
      ans = std::max(ans, a[s[j]] * (s[s.size() - 1] - s[j - 1]));
    }
  }

  std::cout << ans << "\n";

  return 0;
}