/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2025-09-08
 */
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1e6 + 1;
i64 pow[N];

void init() {
  for (int i = 1; i < N; i++) pow[i] = 1ll * i * i;
}

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> ans;
  
  i64 numerator = 1, denominator = 1;
  int rst = n;
  bool flg = true;

  for (int i = 1; i < N && numerator && rst; i++) {
  }

  if (!flg || numerator != 0 || rst != 0) {
    std::cout << "No\n";
  } else {
    std::cout << "Yes\n";
    for (auto i : ans) std::cout << i << " ";
    std::cout << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  init();

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
