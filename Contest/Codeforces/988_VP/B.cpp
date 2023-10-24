#include <algorithm>
#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 105;
int n;
std::string a[N];
bool check(std::string s, std::string t) { return s.find(t) != std::string::npos; }
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  std::sort(a + 1, a + n + 1, [&](auto lhs, auto rhs) {
    return lhs.length() < rhs.length();
  });
  for (int i = 2; i <= n; i++) {
    if (!check(a[i], a[i - 1])) {
      std::cout << "NO\n";
      return;
    }
  }
  std::cout << "YES\n";
  for (int i = 1; i <= n; i++) std::cout << a[i] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
