#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, a[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    char c;
    std::cin >> c;
    a[i] = c - '0';
  }
  int p = n;
  i64 ans = 0;
  for (int i = 1; i <= n; i++) {
    if (p <= 0) {
      std::cout << -1 << " ";
    } else {
      while (p >= 1 && a[p] == 1) p--;
      if (p <= 0) {
        std::cout << -1 << " ";
        continue;
      }
      ans += (n - i - p + 1);
      std::cout << ans << " ";
      p--;
    }
  }
  std::cout << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
