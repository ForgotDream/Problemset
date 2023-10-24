#include <iostream>

using i64 = long long;

constexpr int N = 3e5 + 50;
int n, pre[N], suf[N], a[N], f[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], suf[a[i]]++;
  i64 ans = 0, sum = 0;
  pre[a[1]]++, suf[a[1]]--;
  sum = 1ll * pre[a[1]] * suf[a[1]];
  for (int i = 2; i < n; i++) {
    sum -= 1ll * pre[a[i]] * suf[a[i]];
    pre[a[i]]++, suf[a[i]]--;
    sum += 1ll * pre[a[i]] * suf[a[i]];
    ans += sum - 1ll * pre[a[i]] * suf[a[i]];
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