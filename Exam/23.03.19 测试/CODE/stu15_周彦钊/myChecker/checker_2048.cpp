#include <bits/stdc++.h>
#include <random>

using i64 = long long;

int main() {
  freopen("2048.in", "w", stdout);
  
  int n = 1e5;
  std::mt19937 rnd(std::time(nullptr));
  
  std::vector<int> a = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
  
  std::cout << n << "\n";
  for (int i = 1; i <= n; i++) {
    std::cout << a[rnd() % a.size()] << " ";
  } 
  
  return 0;
}
