#include <algorithm>
#include <cstring>
#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, m;
i64 a[N], b[N], c[N];
int check(int u) {
  a[1] = u;
  for (int i = 1; i <= n; i++) c[i] = a[i];
  std::sort(c + 1, c + n + 1), std::sort(b + 1, b + n + 1);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = std::max(ans, i - int(std::lower_bound(c + 1, c + n + 1, b[i]) - c - 1));
  }
  return ans;
}
void solve() {
  std::cin >> n >> m;
  for (int i = 2; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) std::cin >> b[i];
  int pre = check(1);
  int lo = 1, hi = m, ans = m + 1;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    if (check(mid) > pre) hi = mid - 1, ans = mid;
    else lo = mid + 1;
  }
  std::cout << 1ll * pre * m + m - ans + 1 << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
