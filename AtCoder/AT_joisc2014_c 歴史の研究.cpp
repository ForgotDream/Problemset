/**
 * @file    AT_joisc2014_c 歴史の研究.cpp
 * @author  ForgotDream
 * @brief   回滚莫队
 * @date    2023-09-05
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, q, a[N], c[N];
std::vector<int> b;
i64 ans[N];
namespace SQRT {
int bln[N], lp[N], rp[N];
struct Query {
  int l, r, id;
  bool operator<(const Query &rhs) const {
    if (bln[l] == bln[rhs.l]) return r < rhs.r;
    return bln[l] < bln[rhs.l];
  }
} qry[N];
void init() {
  int blk = std::sqrt(n), cnt = (n - 1) / blk + 1;
  for (int i = 1; i <= n; i++) bln[i] = (i - 1) / blk + 1;
  for (int i = 1; i <= cnt; i++) lp[i] = (i - 1) * blk + 1, rp[i] = i * blk;
  rp[cnt] = n;
  std::sort(qry + 1, qry + q + 1);
}
int cnt[N];
void add(int u, i64 &val) {
  cnt[c[u]]++, val = std::max(val, 1ll * a[u] * cnt[c[u]]);
}
void rollback(int u) { cnt[c[u]]--; }
i64 brute(int l, int r) {
  static int cnt[N];
  i64 res = 0;
  for (int i = l; i <= r; i++) {
    cnt[c[i]]++, res = std::max(res, 1ll * a[i] * cnt[c[i]]);
  }
  for (int i = l; i <= r; i++) cnt[c[i]]--;
  return res;
}
void solve() {
  int s = 1, t = 0, lst = 0;
  i64 cur = 0;
  for (int i = 1; i <= q; i++) {
    auto [l, r, id] = qry[i];
    if (bln[l] == bln[r]) {
      ans[id] = brute(l, r);
      continue;
    }
    if (bln[l] != lst) {
      while (t > rp[bln[l]]) rollback(t--);
      while (s < rp[bln[l]] + 1) rollback(s++);
      lst = bln[l], cur = 0;
    }
    while (t < r) add(++t, cur);
    i64 tmp = cur, p = s;
    while (p > l) add(--p, tmp);
    while (p < s) rollback(p++);
    ans[id] = tmp;
  }
}
}
void solve() {
  std::cin >> n >> q;
  for (int i = 1; i <= n; i++) std::cin >> a[i], b.push_back(a[i]);
  for (int i = 1; i <= q; i++) {
    std::cin >> SQRT::qry[i].l >> SQRT::qry[i].r;
    SQRT::qry[i].id = i;
  }
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  for (int i = 1; i <= n; i++) {
    c[i] = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
  }
  SQRT::init(), SQRT::solve();
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