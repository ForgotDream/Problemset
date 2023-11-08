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
  int n = 10, m = 10;
  std::uniform_int_distribution uib(1, int(21)), idx(1, n);
  std::cout << n << " " << m << "\n";
  for (int i = 1; i <= n; i++) std::cout << uib(rng) << " \n"[i == n];
  for (int i = 1; i <= m; i++) {
    int l = idx(rng), r = idx(rng), opt = (uib(rng) & 1) + 1;
    if (l > r) std::swap(l, r);
    std::cout << opt << " " << l << " " << r << " ";
    if (opt == 1) std::cout << uib(rng) << "\n";
    else std::cout << "\n";
  }
  return 0;
}
