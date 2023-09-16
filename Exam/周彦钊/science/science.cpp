#include <iostream>

using i64 = long long;

i64 l, r, q;
void solve() {
  std::cin >> l >> r >> q;
  if (q > r) {
    std::cout << "infinity\n";
    return;
  }
  i64 ans = 1;
  for (i64 i = 2; i * i <= q; i++) {
    if (q % i == 0) {
      i64 sum = 0;
      while (q % i == 0) q /= i, sum++;
      ans *= (sum + 1);
    }
  }
  if (q > 1) ans *= 2;
  std::cout << ans << "\n";
}

int main() {
  std::freopen("science.in", "r", stdin);
  std::freopen("science.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}