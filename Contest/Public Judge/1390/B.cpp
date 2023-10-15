#include <cstring>
#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, c, d[N], t[N];
bool check(int mid) i{
  i64 sum = 0;
  for (int i = 1; i <= n; i++) sum += std::max(0ll, t[i] - 1ll * mid * d[i]);
  return sum <= c;
}
void solve() {
  std::cin >> n >> c;
  for (int i = 1; i <= n; i++) std::cin >> t[i] >> d[i];
  int lo = 0; hi = 1e9, ans = 1e9;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    if (check(mid)) hi = mid - 1, ans = mid;
    else lo = mid + 1;
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
