#include <iostream>

using i64 = long long;
using f80 = long double;

constexpr int N = 1e5 + 50;
i64 n;
int d[] = {0, 1, 1, 2, 2, 4, 2, 6, 4, 6, 4, 10, 4};
i64 f[N];

int main() {
  std::freopen("letter.in", "r", stdin);
  std::freopen("letter.out", "w", stdout);

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed;

  std::cin >> n;

  if (n <= 12) {
    std::cout << d[n] << "\n";
    return 0;
  }

  i64 cpy = n;
  f80 ans = n;
  for (int i = 2; i * i <= cpy; i++) {
    if (cpy % i == 0) {
      ans *= 1. * (i - 1) / i;
      while (cpy % i == 0) cpy /= i;
    }
  }
  if (cpy != 1) ans *= 1. * (cpy - 1) / cpy; 

  std::cout << i64(ans) << "\n";

  return 0;
}