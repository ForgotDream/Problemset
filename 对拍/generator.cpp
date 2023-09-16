#include <iostream>
#include <chrono>
#include <random>
#include <numeric>

using f80 = long double;

constexpr int prime[] = {5, 7, 11, 13, 17, 19, 23, 29};
std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution val(1, 20), idx(0, 7);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << val(rng) << " " << prime[idx(rng)] << "\n";
  return 0;
}