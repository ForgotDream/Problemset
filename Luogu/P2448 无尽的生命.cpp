/**
 * @file    P2448 无尽的生命.cpp
 * @author  ForgotDream
 * @brief   BIT
 * @date    2023-11-13
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 50;
i64 k, x[N], y[N], val[N], idx[N];
std::vector<i64> a, b;
struct BIT {
  i64 tree[N];
  void modify(int u, int val) {
    for (int i = u; i <= b.size(); i += i & -i) tree[i] += val;
  }
  i64 query(int u) {
    i64 res = 0;
    for (int i = u; i; i -= i & -i) res += tree[i];
    return res;
  }
} bit;
inline int find(int u) { 
  return std::lower_bound(b.begin(), b.end(), u) - b.begin() + 1; 
}
void solve() {
  std::cin >> k;
  for (int i = 1; i <= k; i++) {
    std::cin >> x[i] >> y[i];
    a.push_back(x[i]), a.push_back(y[i]);
  }
  std::sort(a.begin(), a.end());
  a.erase(std::unique(a.begin(), a.end()), a.end());
  b.push_back(a[0]), val[1] = idx[1] = 1;
  for (int i = 1; i < a.size(); i++) {
    if (a[i] > a[i - 1] + 1) {
      b.push_back(a[i - 1] + 1);
      val[b.size()] = a[i] - a[i - 1] - 1;
      idx[b.size()] = b.size();
    }
    b.push_back(a[i]);
    val[b.size()] = 1;
    idx[b.size()] = b.size();
  }
  for (int i = 1; i <= k; i++) {
    x[i] = find(x[i]), y[i] = find(y[i]);
    std::swap(val[x[i]], val[y[i]]), std::swap(idx[x[i]], idx[y[i]]);
  }
  i64 ans = 0;
  for (int i = b.size(); i; i--) {
    ans += val[i] * bit.query(idx[i] - 1);
    bit.modify(idx[i], val[i]);
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
