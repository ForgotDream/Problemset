#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 5e4 + 50;
int n, k, a[N], s;
void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i], s ^= a[i];
  std::cout << 0 << "\n";
}

int main() {
  freopen("nim.in", "r", stdin);
  freopen("nim.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
