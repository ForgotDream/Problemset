/*
 * @file
 * @author  ForgotDream
 * @brief   
 * @date    2025-09-08
 */
#include <deque>
#include <iostream>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  if (n == 3 || n == 5 || n == 2) {
    std::cout << "No\n";
    return;
  }
  
  std::deque<int> ans;
  if (n % 3 == 0) {
    ans = {2, 2, 2, 3, 3, 6};
  } else if (n % 3 == 1) {
    ans = {1};
  } else {
    ans = {2, 2, 3, 3, 3, 3, 6, 6};
  }

  while (ans.size() < n) {
    int u = ans.front();
    ans.pop_front();
    for (int j = 0; j < 4; j++) ans.push_back(2 * u);
  }

  std::cout << "Yes\n";
  for (auto i : ans) std::cout << i << " ";
  std::cout << "\n";
}


// 1: 1
// 6: 2 2 2 3 3 6
// 8: 2 2 3 3 3 3 6 6

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
