#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 1e5 + 50, M = 15;

int n, nxt[N][M], a[N];
int mn[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  for (int i = n; i >= 1; i--) {
    memcpy(nxt[i], nxt[i + 1], sizeof(nxt[i]));
    nxt[i][a[i]] = i;
  }

  i64 ans = 0;

  std::fill(mn + 1, mn + n + 10, n + 1);

  for (int i = 1; i <= n - 2; i++) {
    for (int d = -10; d <= 10; d++) {
      if (a[i] + d <= 0 || a[i] + d > 10) continue;
      int j = nxt[i + 1][a[i] + d];
      if (!j) continue;
      if (a[j] + d <= 0 || a[j] + d > 10) continue;
      int k = nxt[j + 1][a[j] + d];
      if (!k) continue;
      mn[i] = std::min(mn[i], k);
    }
  }

  for (int i = n; i >= 1; i--) {
    mn[i] = std::min(mn[i], mn[i + 1]);
    ans += 1ll * i * (mn[i + 1] - mn[i]);
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
