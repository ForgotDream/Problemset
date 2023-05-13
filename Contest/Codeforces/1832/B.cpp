#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n, k;
  std::cin >> n >> k;

  std::vector<i64> a(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }

  std::sort(a.begin() + 1, a.end());
  
  std::vector<i64> sum(n + 1);
  for (int i = 1; i <= n; i++) {
    sum[i] = a[i] + sum[i - 1];
  }

  std::vector<i64> f(k + 1);
  for (int i = 0; i <= k; i++) {
    f[i] = sum[n - (k - i)] - sum[2 * i];
  }

  std::cout << *max_element(f.begin(), f.end()) << "\n";

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