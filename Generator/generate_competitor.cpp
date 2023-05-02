#include <bits/stdc++.h>
#include <chrono>

using i64 = long long;

int main() {
  std::mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());
  std::array<int, 5> bucket { 0, 0, 0, 0, 0 };
  for (int i = 1; i <= 100000; i++) {
    bucket[rnd() % 4 + 1]++;
  }
  for (int i = 1; i <= 4; i++) {
    std::cout << bucket[i] << " \n"[i == 4];
  }
  return 0;
}