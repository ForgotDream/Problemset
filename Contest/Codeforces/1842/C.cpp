#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<int> max(n + 1, -inf);
  std::vector f(n, std::vector<int>(2));
  max[a[0]] = 0;
  for (int i = 1; i < n; i++) {
    f[i][0] = std::max(f[i - 1][0], f[i - 1][1]);
    if (max[a[i]] == -inf) {
      max[a[i]] = std::max(f[i - 1][0], f[i - 1][1]) - i;
    } else {
      f[i][1] = max[a[i]] + i + 1;
      max[a[i]] = std::max(max[a[i]], std::max(f[i - 1][0], f[i - 1][1]) - i);
    }
  }
  std::cout << std::max(f[n - 1][0], f[n - 1][1]) << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}