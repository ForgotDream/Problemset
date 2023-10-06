#include <iostream>
#include <chrono>
#include <random>
#include <numeric>

using i64 = long long;

std::random_device rd;
std::mt19937 rng(rd());

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 1e5, m = 2e5;
  std::uniform_int_distribution ud(1, n), udw((int)1e9, (1 << 30) - 1);
  std::cout << n << " " << m << "\n";
  for (int i = 1; i <= m; i++) {
    auto u = ud(rng), v = ud(rng), w = udw(rng);
    while (u == v) {
      u = ud(rng), v = ud(rng), w = udw(rng);
    }
    std::cout << u << " " << v << " " << w << "\n";
  }
  return 0;
}
