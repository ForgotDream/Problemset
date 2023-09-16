#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, m;
i64 a[N];
bool check(i64 val) {
  i64 res = 0;
  for (int i = 1; i <= n;) {
    int j = i;
    i64 len = 0;
    res++;
    while (j <= n && len + a[j] <= val) {
      len += a[j] + 1, j++;
    }
    i = j;
  }
  return res <= m;
}
void solve() {
  std::cin >> n >> m;
  i64 max = 0;
  for (int i = 1; i <= n; i++) std::cin >> a[i], max = std::max(max, a[i]);
  i64 lo = max, hi = 1e15, ans = hi;
  while (lo <= hi) {
    i64 mid = (lo + hi) >> 1;
    if (check(mid)) hi = mid - 1, ans = mid;
    else lo = mid + 1;
  }
  std::cout << ans << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}