#include <iostream>
#include <string>

using i64 = long long;

std::string s;
void solve() {
  std::cin >> s;
  for (int i = 1; i < s.length(); i++) {
    if (s[i] >= s[i - 1]) {
      std::cout << "No\n";
      return;
    }
  }
  std::cout << "Yes\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
