#include <bits/stdc++.h>

using i64 = long long;

std::string s;

void solve() {
  std::cin >> s;
  s.back() = '4';
  std::cout << s << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
