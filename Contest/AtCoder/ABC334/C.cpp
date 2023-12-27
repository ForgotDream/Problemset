#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;
int k, n, a[N], cnt[N];
std::vector<int> b;
i64 pre[N], suf[N];

void solve() {
  std::cin >> n >> k;
  std::fill(cnt + 1, cnt + n + 1, 2);
  for (int i = 1; i <= k; i++) std::cin >> a[i];

  if (k & 1) {
    pre[1] = suf[k] = a[k] - a[1];
    for (int i = 2; i <= k; i++) pre[i] = pre[i - 2] + (a[i] - a[i - 1]);
    for (int i = k - 1; i; i--) suf[i] = suf[i + 2] + (a[i + 1] - a[i]);

    i64 ans = 1e18;
    for (int i = 1; i <= k; i++) ans = std::min(ans, pre[i - 1] + suf[i + 1]);

    std::cout << ans << "\n";
  } else {
    i64 ans = 0;
    for (int i = 1; i <= k; i += 2) ans += a[i + 1] - a[i];
    std::cout << ans << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
