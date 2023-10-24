/**
 * @file    LOJ#2732 「JOISC 2016 Day 2」雇佣计划.cpp
 * @author  ForgotDream
 * @brief   BIT
 * @date    2023-10-18
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;
int n, m, a[N];
std::vector<int> b;
struct Query {
  int opt, pos, val;
} query[N];
struct SegTree {
  int tree[2 * N];
  void modify(int u, int val) {
    for (int i = u; i < 2 * N; i += i & -i) tree[i] += val;
  }
  int query(int u) {
    int res = 0;
    for (int i = u; i; i -= i & -i) res += tree[i];
    return res;
  }
} bit1, bit2;
int id(int u) {
  return std::lower_bound(b.begin(), b.end(), u) - b.begin() + 1;
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i], b.push_back(a[i]);
  for (int i = 1; i <= m; i++) {
    std::cin >> query[i].opt;
    if (query[i].opt == 1) std::cin >> query[i].val;
    else std::cin >> query[i].pos >> query[i].val;
    b.push_back(query[i].val);
  }
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  for (int i = 1; i <= n; i++) a[i] = id(a[i]), bit1.modify(a[i], 1);
  for (int i = 1; i < n; i++) bit2.modify(std::min(a[i], a[i + 1]), 1);
  for (int i = 1; i <= m; i++) {
    auto [opt, pos, val] = query[i];
    if (opt == 1) {
      val = id(val);
      // std::cout << "#" << bit1.query(val - 1) << " " << bit2.query(val - 1) << "\n";
      std::cout << bit2.query(val - 1) - bit1.query(val - 1) + 1 << "\n";
    } else {
      bit1.modify(a[pos], -1);
      if (pos != 1) bit2.modify(std::min(a[pos], a[pos - 1]), -1);
      if (pos != n) bit2.modify(std::min(a[pos], a[pos + 1]), -1);
      a[pos] = id(val);
      bit1.modify(a[pos], 1);
      if (pos != 1) bit2.modify(std::min(a[pos], a[pos - 1]), 1);
      if (pos != n) bit2.modify(std::min(a[pos], a[pos + 1]), 1);
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
