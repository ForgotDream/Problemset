#include <bits/stdc++.h>
#include <climits>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<i64> a(n);
  i64 max = LONG_LONG_MIN, semax = max;
  i64 min = LONG_LONG_MAX, semin = min;
  std::vector<int> pivot(4);

  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    if (max <= a[i]) {
      semax = max, max = a[i];
      pivot[1] = pivot[0], pivot[0] = i;
    } else if (semax <= a[i]) {
      semax = a[i];
      pivot[1] = i;
    }
    if (min >= a[i]) {
      semin = min, min = a[i];
      pivot[3] = pivot[2], pivot[2] = i;
    } else if (semin >= a[i]) {
      semin = a[i];
      pivot[3] = i;
    }
  }

  i64 ans = std::max(max * semax, min * semin);
  if (pivot[0] != pivot[3]) {
    ans = std::max(ans, max * semin);
  }
  if (pivot[1] != pivot[2]) {
    ans = std::max(ans, semax * min);
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