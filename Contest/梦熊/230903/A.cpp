#include <cmath>
#include <iomanip>
#include <iostream>

using i64 = long long;
using f80 = long double;

constexpr int N = 1e6 + 50;
int x, y, n;
namespace X_EQUALS_TO_0 {
f80 f[N];
f80 solve() {
  for (int i = 1; i <= y; i++) f[i] = f[i - 1] + f80(1) / i;
  return f[y];
}
}  // namespace X_EQUALS_TO_0
namespace Y_EQUALS_TO_0 {
f80 f[N];
f80 solve() {
  for (int i = 1; i <= x; i++) f[i] = 1 + f[i - 1] / (2 * i - 1);
  return f[x];
}
}  // namespace Y_EQUALS_TO_0
namespace FULL_COMBO {
f80 fac[] = {1, 1, 2, 6, 24, 120, 720, 5040};
f80 C(int n, int m) { return fac[n] / fac[m] / fac[n - m]; }
f80 solve() {
  X_EQUALS_TO_0::solve();
  Y_EQUALS_TO_0::solve();
  f80 res = 0;
  for (int i = 0; i <= y; i++) {
    f80 sth = C(y, i) * fac[i + 2 * x] * fac[y - i];
    std::cerr << sth << " ";
    res += sth * X_EQUALS_TO_0::f[y - i];
    std::cerr << X_EQUALS_TO_0::f[y - i] << "\n";
  }
  std::cerr << Y_EQUALS_TO_0::f[x] << "\n";
  return res / fac[2 * x + y] + Y_EQUALS_TO_0::f[x];
}
}  // namespace FULL_COMBO
void solve() {
  std::cin >> x >> y, n = 2 * x + y;
  if (x == 0) {
    std::cout << X_EQUALS_TO_0::solve() << "\n";
  } else if (y == 0) {
    std::cout << Y_EQUALS_TO_0::solve() << "\n";
  } else {
    std::cout << FULL_COMBO::solve() << "\n";
  }
}

int main() {
  std::freopen("island.in", "r", stdin);
  std::freopen("island.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(16);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}