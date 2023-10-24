#include <iostream>
#include <cmath>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, q;
i64 v[N], t[N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> v[i], v[i] += v[i - 1];
  i64 X = 0;
  for (int i = 1; i <= n; i++) X = std::max(X, i64(std::ceil(1. * v[i] / i)));
  std::cin >> q;
  for (int i = 1; i <= q; i++) {
    std::cin >> t[i];
    if (t[i] < X) std::cout << -1 << "\n";
    else std::cout << i64(std::ceil(1. * v[n] / t[i])) << "\n";
  }

  return 0;
}