/**
 * @file    CF1858E2 Rollbacks (Hard Version).cpp
 * @author  ForgotDream
 * @brief   Ad Hoc + BIT
 * @date    2023-10-02
 */
#include <iostream>
#include <set>
#include <stack>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 1e6 + 50;
int q;
std::set<int> col[N];
struct BIT {
  int tree[N];
  void modify(int u, int val) {
    for (int i = u; i < N; i += i & -i) tree[i] += val;
  }
  int query(int u) {
    int res = 0;
    for (int i = u; i; i -= i & -i) res += tree[i];
    return res;
  }
} bit;
int a[N];
void solve() {
  std::cin >> q;
  int p = 0;
  std::stack<pii> reg;
  while (q--) {
    char opt;
    std::cin >> opt;
    if (opt == '+') {
      int x;
      std::cin >> x, ++p;
      reg.emplace(2, a[p]);
      if (a[p]) {
        if (!col[a[p]].empty()) bit.modify(*col[a[p]].begin(), -1);
        col[a[p]].erase(p);
        if (!col[a[p]].empty()) bit.modify(*col[a[p]].begin(), 1);
      }
      a[p] = x;
      if (!col[a[p]].empty()) bit.modify(*col[a[p]].begin(), -1);
      col[a[p]].insert(p);
      bit.modify(*col[a[p]].begin(), 1);
    } else if (opt == '-') {
      int k;
      std::cin >> k, reg.emplace(1, p), p -= k;
    } else if (opt == '?') {
      std::cout << bit.query(p) << std::endl; 
    } else {
      auto [typ, val] = reg.top();
      reg.pop();
      if (typ == 1) {
        p = val;
      } else {
        if (!col[a[p]].empty()) bit.modify(*col[a[p]].begin(), -1);
        col[a[p]].erase(p);
        if (!col[a[p]].empty()) bit.modify(*col[a[p]].begin(), 1);
        a[p] = val;
        if (val != 0) {
          if (!col[a[p]].empty()) bit.modify(*col[a[p]].begin(), -1);
          col[a[p]].insert(p);
          bit.modify(*col[a[p]].begin(), 1);
        }
        p--;
      }
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
