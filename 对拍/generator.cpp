#include <iostream>
#include <chrono>
#include <random>
#include <numeric>

using i64 = long long;

std::random_device rd;
std::mt19937 rng(rd());
int dep(i64 num) { return 64 - __builtin_clzll(num); }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << 1 << "\n";
  std::uniform_int_distribution<i64> N(1, i64(1e18));
  i64 n = N(rng);
  int mdep = dep(n);
  std::uniform_int_distribution<i64> X(1, n);
  i64 x = X(rng);
  int cdep = dep(x);
  std::cout << n << " " << x << " " << mdep - cdep << "\n";
  return 0;
}
