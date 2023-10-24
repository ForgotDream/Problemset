/**
 * @file    P5906 【模板】回滚莫队&不删除莫队.cpp
 * @author  ForgotDream
 * @brief   回滚莫队
 * @date    2023-09-05
 */
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;
int n, q, a[N], ans[N];
std::vector<int> b;
namespace SQRT {
int bln[N], lp[N], rp[N];
struct Query {
  int l, r, id;
  bool operator<(const Query &rhs) const {
    if (bln[l] != bln[rhs.l]) return bln[l] < bln[rhs.l];
    return r < rhs.r;
  }
} qry[N];
void init() {
  int blk = std::max(q / std::sqrt(n), 1.), cnt = (n - 1) / blk + 1;
  for (int i = 1; i <= n; i++) bln[i] = (i - 1) / blk + 1;
  for (int i = 1; i <= cnt; i++) lp[i] = (i - 1) * blk + 1, rp[i] = i * blk;
  rp[cnt] = n;
  std::sort(qry + 1, qry + q + 1);
}
int s = 1, t = 0, cur = 0;
int b[N], lb[N], rb[N], lpre[N], rpre[N];
std::stack<pii> ls, rs;
void add(int u, int &val) {
  lpre[u] = lb[a[u]], rpre[u] = rb[a[u]];
  if (lb[a[u]] > u) lb[a[u]] = u;
  if (rb[a[u]] < u) rb[a[u]] = u;
  val = std::max(rb[a[u]] - lb[a[u]], val);
}
void rollback(int u) {
  lb[a[u]] = lpre[u], rb[a[u]] = rpre[u];
}
void solve() {
  int pre = 0;
  for (int i = 1; i <= n; i++) lb[i] = lpre[i] = 1e9;
  for (int i = 1; i <= q; i++) {
    auto [l, r, id] = qry[i];
    if (bln[l] == bln[r]) {
      int cur = 0;
      for (int j = l; j <= r; j++) {
        if (!b[a[j]]) b[a[j]] = j;
        else cur = std::max(cur, j - b[a[j]]);
      }
      for (int j = l; j <= r; j++) {
        if (b[a[j]]) b[a[j]] = 0;
      }
      ans[id] = cur;
      continue;
    }
    if (bln[l] != pre) {
      for (int i = s; i <= t; i++) {
        lb[a[i]] = lpre[a[i]] = 1e9;
        rb[a[i]] = rpre[a[i]] = 0;
      }
      s = rp[bln[l]] + 1, t = s - 1;
      pre = bln[l], cur = 0;
    }
    while (r > t) add(++t, cur);
    int tmp = cur;
    while (l < s) add(--s, tmp);
    while (s < rp[bln[l]] + 1) rollback(s++);
    ans[id] = tmp;
  }
}
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], b.push_back(a[i]);
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  for (int i = 1; i <= n; i++) {
    a[i] = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
  }
  std::cin >> q;
  using SQRT::qry;
  for (int i = 1; i <= q; i++) {
    std::cin >> qry[i].l >> qry[i].r, qry[i].id = i;
  }
  SQRT::init();
  SQRT::solve();
  for (int i = 1; i <= q; i++) std::cout << ans[i] << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}