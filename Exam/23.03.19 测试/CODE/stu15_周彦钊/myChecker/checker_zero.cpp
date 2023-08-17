#include <bits/stdc++.h>
#include <random>

int main() {
  freopen("zero.in", "w", stdout);
  
  int n = 200;
  std::mt19937 rnd(std::time(nullptr));
  
  std::cout << n << "\n";
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << int(rnd() % ((int)2e8 + 50) - 1e8) << " \n"[j == n - 1];
    }
  }
  
  return 0;
}
