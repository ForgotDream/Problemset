#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::string s;
  std::cin >> n >> s;

  bool flg = (s[0] == '<');
  int ans = 1, cur = 1;
  for (int i = 1; i < n; i++) {
    if (s[i] == '<') {
      if (flg) {
        cur += 1;
      } else {
        ans = std::max(ans, cur);
        cur = 1;
        flg = true;
      }
    } else {
      if (!flg) {
        cur += 1;
      } else {
        ans = std::max(ans, cur);
        cur = 1;
        flg = false;
      }
    }
  }

  ans = std::max(cur, ans);

  std::cout << ans + 1 << "\n";
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