#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  std::string s;
  std::cin >> s;

  if (s.length() <= 3) {
    std::cout << "NO\n";
    return;
  }

  int cnt = std::count(s.begin(), s.end(), s[0]);
  if (cnt == s.length() || cnt == s.length() - 1) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";
  }

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