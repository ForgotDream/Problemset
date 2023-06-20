#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  u64 s = 0;
  for (int i = 0; i < 64; i++) {
    u64 c;
    std::cin >> c;
    s += c * (1ull << i);
  }
  std::cout << s << "\n";

  return 0;
}