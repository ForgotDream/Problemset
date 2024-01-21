#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2e5 + 50;

int n, a[N], b[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) std::cin >> b[i];

  std::sort(a + 1, a + n + 1);
  std::sort(b + 1, b + n + 1);

  for (int i = 1; i <= n; i++) {
    int hi = a[i] + b[1];
    int lo = b[n] - a[i];

    auto it1 = std::upper_bound(a + 1, a + n + 1, lo);
    auto it2 = std::lower_bound(a + 1, a + n + 1, hi) - 1;

    if (it1 == a + n + 1) break;

    if (it1 <= it2) {
      std::cerr << i << " " << *it1 << " " << *it2 << "\n";
      std::cout << "Alice\n";
      return;
    }
  }
  std::cout << "Bob\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
