/**
 * @file    CF863E Turn Off The TV.cpp
 * @author  ForgotDream
 * @brief   ST
 * @date    2023-10-27
 */
#include <algorithm>
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 6e5 + 50;
int n, m;
std::vector<int> b;
pii a[N];
int find(int u) {
  return std::lower_bound(b.begin(), b.end(), u) - b.begin() + 1;
}
struct st {
  int st[20][N];
  void init() {
    for (int i = 1; i <= n; i++) {
      auto [l, r] = a[i];
      l = find(l), r = find(r);
      st[0][l]++, st[0][r + 1]--;
    }
    for (int i = 1; i <= m; i++) st[0][i] += st[0][i - 1];
    for (int i = 1; i <= std::__lg(m); i++) {
      for (int j = 1; j <= m - (1 << i) + 1; j++) {
        st[i][j] = std::min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  int query(int l, int r) {
    int d = std::__lg(r - l + 1);
    return std::min(st[d][l], st[d][r - (1 << d) + 1]);
  }
} st;
void solve() {
  std::cin >> n;
  for (int i = 1, l, r; i <= n; i++) {
    std::cin >> l >> r;
    b.push_back(l), b.push_back(r), b.push_back(r + 1);
    a[i] = std::make_pair(l, r);
  }
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  m = b.size(), st.init();
  for (int i = 1; i <= n; i++) {
    auto [l, r] = a[i];
    l = find(l), r = find(r);
    if (st.query(l, r) >= 2) {
      std::cout << i << "\n";
      return;
    }
  }
  std::cout << -1 << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
