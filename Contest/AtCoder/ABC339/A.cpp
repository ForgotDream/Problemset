#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

std::string s;

void solve() {
  std::cin >> s;
  auto it = std::find(s.rbegin(), s.rend(), '.');
  std::cout << std::string(it.base(), s.end()) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
