#include <iostream>
#include <chrono>
#include <random>

using f80 = long double;

void compile() {
  system("g++ generator.cpp -o g -std=c++20 -O2");
  system("g++ std.cpp -o std -std=c++20 -O2");
  system("g++ checker.cpp -o checker -std=c++20 -O2");
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  compile();
  while (true) {
    system("./g > tmp.in");
    system("./checker < tmp.in > checker.out");
    auto tbe = std::chrono::system_clock::now().time_since_epoch().count();
    system("./std < tmp.in > std.out");
    auto ted = std::chrono::system_clock::now().time_since_epoch().count();
    std::cerr << "Used Time: " << (ted - tbe) / 1e9 << "\n";
    if (system("diff std.out checker.out")) break;
  }
  // system("pause");
  return 0;
}
