/**
 * @file    CF85D Sum of Medians.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-09-08
 */
#include <iostream>
#include <vector>

using i64 = long long;

int n;
std::vector<int> a;
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::string opt;
    int val;
    std::cin >> opt;
    if (opt == "add") {
      std::cin >> val;
      a.insert(std::lower_bound(a.begin(), a.end(), val), val);
    } else if (opt == "del") {
      std::cin >> val;
      a.erase(std::lower_bound(a.begin(), a.end(), val));
    } else {
      i64 res = 0;
      for (int i = 2; i < a.size(); i += 5) res += a[i];
      std::cout << res << '\n';
    }
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  int t = 1;
  // fin >> t;
  while (t--) solve();
  return 0;
}