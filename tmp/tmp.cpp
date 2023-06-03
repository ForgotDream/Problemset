/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-06-03
 */
#include <bits/stdc++.h>

using i64 = long long;

struct Solver {
  int n, q;
  std::vector<int> a, curCol, col;

  Solver(int _n, int _q) { n = _n, q = _q; }

  void in() {
    a.resize(n);
    for (int i = 0; i < n; i++) {
      std::cin >> a[i];
    }
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  Solver solver(n, m);
  solver.in();

  return 0;
}
