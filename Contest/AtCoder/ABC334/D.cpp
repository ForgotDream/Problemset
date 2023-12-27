#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, q;
i64 a[N];

void solve() {
  std::cin >> n >> q;
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  std::sort(a + 1, a + n + 1);
  std::partial_sum(a + 1, a + n + 1, a + 1);

  for (i64 x; q; q--) {
    std::cin >> x;
    auto it = std::lower_bound(a + 1, a + n + 1, x);
    if (*it != x) it--;
    std::cout << (it - a) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
