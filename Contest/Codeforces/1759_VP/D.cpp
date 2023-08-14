#include <bits/stdc++.h>
#define int long long
using i64 = long long;
int t, n, m;
void solve() {
  std::cin >> n >> m;
  int c2 = 0, c5 = 0;
  while (n % 2 == 0) n /= 2, c2++;
  while (n % 5 == 0) n /= 5, c5++;
  int len = std::min(c2, c5);
  
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> t;
  while (t--) solve();
  return 0;
}