#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

std::string s;

void solve() {
  std::cin >> s;
  for (char c = 'a'; c <= 'z'; c++) {
    if (std::count(s.begin(), s.end(), c) == 1) {
      std::cout << std::find(s.begin(), s.end(), c) - s.begin() + 1 << "\n";
      return;
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
