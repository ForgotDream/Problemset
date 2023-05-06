#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  std::string s;
  std::cin >> s;

  if (s == "^") {
    std::cout << 1 << "\n";
    return;
  }

  int len = s.length();
  int flg = 0;
  int cnt = 0, ans = 0;
  for (int i = 0; i < len; i++) {
    if (s[i] == '_') {
      cnt++;
    } else {
      if (cnt != 0) {
        ans += cnt - 1 + (flg ^ 1);
        cnt = 0;
      }
      flg = 1;
    }
  }
  ans += cnt + (flg ^ 1);

  std::cout << ans << "\n";

  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}