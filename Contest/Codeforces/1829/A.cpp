#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  std::string s, t = "codeforces";
  std::cin >> s;
  int ans = 0;
  for (int i = 0; i < 10; i++) {
    if (s[i] != t[i]) {
      ans++;
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