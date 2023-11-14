#include <iostream>
#include <string>

using i64 = long long;

int n;
std::string s;
void solve() {
  std::cin >> n >> s;
  std::cout << s[n - 1] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
