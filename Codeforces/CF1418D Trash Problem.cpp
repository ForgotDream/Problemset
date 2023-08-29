/**
 * @file    CF1418D Trash Problem.cpp
 * @author  ForgotDream
 * @brief   这啥玩意啊
 * @date    2023-08-27
 */
#include <iostream>
#include <set>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, q;
i64 p[N];
std::set<i64> s;
std::multiset<i64> f;
void insert(i64 val) {
  auto it = s.insert(val).first;
  if (it != s.begin()) f.insert(*it - *std::prev(it));
  if (it != std::prev(s.end())) f.insert(*std::next(it) - *it);
  if (it != s.begin() && it != std::prev(s.end())) {
    f.erase(f.find(*std::next(it) - *std::prev(it)));
  }
}
void erase(i64 val) {
  auto it = s.find(val);
  if (it != s.begin()) f.erase(f.find(*it - *std::prev(it)));
  if (it != std::prev(s.end())) f.erase(f.find(*std::next(it) - *it));
  if (it != s.begin() && it != std::prev(s.end())) {
    f.insert(*std::next(it) - *std::prev(it));
  }
  s.erase(it);
}
i64 query() {
  if (s.size() < 2) return 0;
  return *s.rbegin() - *s.begin() - *f.rbegin();
}
void solve() {
  std::cin >> n >> q;
  for (int i = 1; i <= n; i++) std::cin >> p[i], insert(p[i]);
  std::cout << query() << "\n";
  for (int i = 1; i <= q; i++) {
    int opt, val;
    std::cin >> opt >> val;
    if (opt == 0) erase(val);
    else insert(val);
    std::cout << query() << "\n";
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}