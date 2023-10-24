#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  i64 n;
  std::cin >> s >> n;

  std::reverse(s.begin(), s.end());

  i64 ans = 0;
  for (int i = s.length() - 1; i >= 0; i--) {
    ans += (s[i] == '1') * (1ll << i);
  }

  if (ans > n) {
    std::cout << -1 << "\n";
    return 0;
  }

  for (i64 i = s.length() - 1; i >= 0; i--) {
    if (s[i] == '?') {
      if (ans + (1ll << i) <= n) {
        ans += (1ll << i);
      }
    }
  }

  std::cout << ans << "\n";

  return 0;
}