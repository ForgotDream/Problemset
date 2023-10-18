/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-10-18
 */
#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m;
struct Node {
  int price, cnt;
  bool operator(const Node &rhs) const {
    return price < rhs.price;
  }
} a[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i].price >> a[i].cnt;
  std::sort(a + 1, a + n + 1);
  int p = 1;
  while (p <= n && a[p].price < m / 2) p++;
  p--;
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
