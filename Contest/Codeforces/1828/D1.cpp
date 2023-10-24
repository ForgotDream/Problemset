#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<i64> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector f(n + 1, std::vector<i64>(n + 1));
  auto min = f, max = f;
  for (int len = 1; len <= n; len++) {
    for (int l = 0; l + len - 1 < n; l++) {
      int r = l + len - 1;
      if (len == 1) {
        f[l][r] = 0;
        min[l][r] = max[l][r] = a[l];
        continue;
      }
      min[l][r] = std::min(min[l][r - 1], min[l + 1][r]);
      max[l][r] = std::max(max[l][r - 1], max[l + 1][r]);
      f[l][r] = r - l;
      if (a[l] < min[l + 1][r]) {
        f[l][r] = std::min(f[l][r], f[l + 1][r]);
      }
      if (a[r] > max[l][r - 1]) {
        f[l][r] = std::min(f[l][r], f[l][r - 1]);
      }
    }
  }

  i64 ans = 0;
  for (int len = 1; len <= n; len++) {
    for (int l = 0; l + len - 1 < n; l++) {
      int r = l + len - 1;
      ans += f[l][r];
    }
  }

  std::cout << ans << "\n";

  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}