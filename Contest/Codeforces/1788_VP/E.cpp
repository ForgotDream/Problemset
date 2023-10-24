#include <climits>
#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, a[N];
i64 s[N], f[N], g[N];

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], s[i] = s[i - 1] + a[i];

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      if (s[i] - s[j - 1] < 0) continue;
      f[i] = std::max(f[i], g[j - 1] + (i - j + 1));
    }
    g[i] = std::max(g[i - 1], f[i]);
  }

  std::cout << *std::max_element(f + 1, f + n + 1) << "\n";

  return 0;
}