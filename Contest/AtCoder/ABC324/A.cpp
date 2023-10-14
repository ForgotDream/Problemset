#include <iostream>

using i64 = long long;

int n;
void solve() {
  std::cin >> n;
  int lst;
  for (int i = 1, u; i <= n; i++) {
    std::cin >> u;
    if (i == 1) {
      lst = u;
    } else {
      if (lst != u) {
        std::cout << "No\n";
        return;
      }
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
