#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 2050;
int n, k, a[N];
bool used[N];
bool check(int u) {
  for (int i = 1; i <= n; i++) used[i] = false;
  int res = 0;
  while (true) {
    int rst = u;
    bool flg = false;
    for (int i = n; i;) {
      while (i && (a[i] > rst || used[i])) i--;
      if (i) rst -= a[i], flg = used[i] = true;
      else break;
    }
    if (!flg) break;
    else res++;
  }
  return res <= k;
}
void solve() {
  std::cin >> n >> k;
  int mx = 0;
  for (int i = 1; i <= n; i++) std::cin >> a[i], mx = std::max(mx, a[i]);
  std::sort(a + 1, a + n + 1);
  int lo = mx, hi = 1e9, ans = hi;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    if (check(mid)) hi = mid - 1, ans = mid;
    else lo = mid + 1;
  }
  std::cout << ans << "\n";
}

int main() {
  freopen("trans.in", "r", stdin);
  freopen("trans.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
