#include <iostream>
#include <cmath>
#include <cstring>

using i64 = long long;

constexpr int N = 3e5 + 50;
int t, n, h[N], d[N][2];
i64 cnt[3];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> h[i];
  int max = *std::max_element(h + 1, h + n + 1);
  for (int i = 1; i <= n; i++) d[i][0] = max - h[i], d[i][1] = max - h[i] + 1;
  i64 ans = 1e18;
  for (int j = 0; j < 2; j++) {
    std::memset(cnt, 0, sizeof(cnt));
    // 1 -> +1, 2 -> +2
    for (int i = 1; i <= n; i++) {
      cnt[1] += d[i][j] % 2, cnt[2] += d[i][j] / 2;
    }
    i64 lo = 0, hi = cnt[2], cur = cnt[2];
    while (lo <= hi) {
      i64 mid = (lo + hi) >> 1;
      if (cnt[2] - mid > cnt[1] + 2 * mid + 1) lo = mid + 1;
      else hi = mid - 1, cur = mid;
    }
    cnt[2] -= cur;
    cnt[1] += 2 * cur;
    if (cnt[1] > cnt[2]) ans = std::min(ans, 2 * cnt[1] - 1);
    else ans = std::min(ans, 2 * cnt[2]);
  }
  std::cout << ans << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> t;
  
  while (t--) solve();

  return 0;
}