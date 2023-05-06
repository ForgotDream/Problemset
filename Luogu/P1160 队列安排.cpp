/**
 * @file    P1160 队列安排.cpp
 * @author  ForgotDream
 * @brief   Link List
 * @date    2023-05-05
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> l(n + 1, 0), r(n + 1, 0);
  for (int i = 2; i <= n; i++) {
    int k, p;
    std::cin >> k >> p;
    if (p) {
      l[r[k]] = i, r[i] = r[k];
      r[k] = i, l[i] = k;
    } else {
      r[l[k]] = i, l[i] = l[k];
      l[k] = i, r[i] = k;
    }
  }

  int m;
  std::cin >> m;

  std::vector<bool> deleted(n);
  while (m--) {
    int x;
    std::cin >> x;
    if (deleted[x]) {
      continue;
    }
    deleted[x] = true;
    r[l[x]] = r[x], l[r[x]] = l[x];
  }

  int pivot = -1;
  for (int i = 1; i <= n; i++) {
    if (!deleted[i] && l[i] == 0) {
      pivot = i;
      break;
    }
  }

  while (pivot) {
    std::cout << pivot << " ";
    pivot = r[pivot];
  }
  std::cout << "\n";

  return 0;
}