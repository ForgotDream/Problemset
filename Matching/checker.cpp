#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;
i64 n, k, m, c, d, a[N], b[N];
i64 calc() {
  std::copy(a + 1, a + n + 1, b + 1);
  std::nth_element(b + 1, b + k, b + n + 1);
  return b[k];
}
void solve() {
  std::cin >> n >> k >> m >> c >> d;
  k = n - k + 1;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= m; i++) a[i] += c + (i - 1) * d;
  i64 ans = calc();
  for (int i = m + 1; i <= n; i++) {
    a[i - m] -= c;
    a[i] += c + m * d;
    for (int j = i - m + 1; j <= i; j++) a[j] -= d;
    ans = std::max(ans, calc());
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
