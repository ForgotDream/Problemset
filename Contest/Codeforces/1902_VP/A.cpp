#include <bits/stdc++.h>

using i64 = long long;

int n;
std::string s;

void solve() {
  std::cin >> n >> s;

  if (std::count(s.begin(), s.end(), '1') != n) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
