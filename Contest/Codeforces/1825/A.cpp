#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  std::string s;
  std::cin >> s;

  int ans = -1;
  for (int len = 1; len <= s.length(); len++) {
    for (int l = 0; l + len - 1 < s.length(); l++) {
      int r = l + len - 1;
      int p1 = l, p2 = r;
      bool flg = false;
      while (p1 <= p2) {
        if (s[p1] != s[p2]) {
          ans = len;
          flg = true;
          break;
        }
        p1++, p2--;
      }
      if (flg) {
        break;
      }
    }
  }

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