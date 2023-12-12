#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 2.5e5 + 50;
int n;
i64 a[N], s, f[N], sum[N], ans;
void solve() {
  std::cin >> n >> s;
  for (int i = 1, j = 1; i <= n; i++) {
    std::cin >> a[i], sum[i] = sum[i - 1] + a[i];
    while (sum[i] - sum[j - 1] > s) j++;
    f[i] = (i - j + 1) + (j - 1) + f[j - 1], ans += f[i];
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
