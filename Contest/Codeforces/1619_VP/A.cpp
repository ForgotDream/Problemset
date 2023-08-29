#include <iostream>
#include <string>

using i64 = long long;

std::string s;
void solve() {
  std::cin >> s;
  int n = s.length();
  if (n & 1) {
    std::cout << "NO\n";
    return;
  }
  std::cerr << s.substr(0, n / 2) << " " << s.substr(n / 2) << "\n";
  if (s.substr(0, n / 2) == s.substr(n / 2)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}