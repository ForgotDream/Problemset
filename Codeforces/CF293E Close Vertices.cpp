/**
 * @file    CF293E Close Vertices.cpp
 * @author  ForgotDream
 * @brief   点分治
 * @date    2023-09-08
 */
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 1e5 + 50;
int n, l, a;
std::vector<pii> adj[N];
int siz[N], max[N], sum;
bool valid[N];
int rt, dep[N], d[N], cnt;
pii q[N];
class BIT {
 private:
  i64 tree[N];
 public:
  void modify(int u, int val) {
    if (u <= 0) return;
    for (int i = u; i < N; i += i & -i) tree[i] += val;
  }
  i64 query(int u) {
    if (u <= 0) return 0;
    i64 res = 0;
    for (int i = u; i; i -= i & -i) res += tree[i];
    return res;
  }
} bit;
void calcsiz(int u, int frm) {
  siz[u] = 1, max[u] = 0;
  for (auto [v, w] : adj[u]) {
    if (v == frm || valid[v]) continue;
    calcsiz(v, u);
    siz[u] += siz[v], max[u] = std::max(max[u], siz[v]);
  }
  max[u] = std::max(max[u], sum - siz[u]);
  if (max[u] < max[rt]) rt = u;
}
void calcdis(int u, int frm) {
  q[++cnt] = std::pair(d[u], dep[u]);
  if (dep[u] >= ::l) return;
  for (auto [v, w] : adj[u]) {
    if (v == frm || valid[v]) continue;
    dep[v] = dep[u] + 1, d[v] = d[u] + w;
    calcdis(v, u);
  }
}
i64 calc(int u, int w, int d) {
  d[u] = w, dep[u] = d, cnt = 0;
  calcdis(u, 0);
  std::sort(q + 1, q + cnt + 1);
  for (int i = 1; i <= cnt; i++) bit.modify(q[i].second + 1, 1);
  int l = 1, r = cnt;
  i64 res = 0;
  while (l < r) {
    if (q[l].first + q[r].first <= ::a) {
      bit.modify(q[l].second + 1, -1);
      res += bit.query(::l - q[l].second + 1), l++;
    } else {
      bit.modify(q[r].second + 1, -1);
      r--;
    }
  }
  bit.modify(q[l].second + 1, -1);
  return res;
}
i64 ans = 0;
void dfz(int u, int frm) {
  valid[u] = true, ans += calc(u, 0, 0);
  for (auto [v, w] : adj[u]) {
    if (v == frm || valid[v]) continue;
    ans -= calc(v, w, 1);
    sum = siz[v], rt = 0, max[rt] = 1e9;
    calcsiz(v, u), dfz(rt, u);
  }
}
void solve() {
  std::cin >> n >> l >> a;
  for (int u = 2, v, w; u <= n; u++) {
    std::cin >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  rt = 0, max[rt] = 1e9, sum = n;
  calcsiz(1, 0), dfz(rt, 0);
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}