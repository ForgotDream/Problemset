/**
 * @file    P4178 Tree.cpp
 * @author  ForgotDream
 * @brief   点分治
 * @date    2023-09-09
 */
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 1e5 + 50;
int n, l, w;
std::vector<pii> adj[N];
int siz[N], max[N], sum;
bool vis[N];
int rt, dep[N], dis[N];
int q[N], cnt;
void calcsiz(int u, int frm) {
  siz[u] = 1, max[u] = 0;
  for (auto [v, w] : adj[u]) {
    if (v == frm || vis[v]) continue;
    calcsiz(v, u);
    siz[u] += siz[v], max[u] = std::max(max[u], siz[v]);
  }
  max[u] = std::max(max[u], sum - siz[u]);
  if (max[u] < max[rt]) rt = u;
}
void calcdis(int u, int frm) {
  q[++cnt] = dis[u];
  for (auto [v, w] : adj[u]) {
    if (v == frm || vis[v]) continue;
    dis[v] = dis[u] + w;
    calcdis(v, u);
  }
}
i64 calc(int u, int w) {
  dis[u] = w, cnt = 0;
  calcdis(u, 0);
  std::sort(q + 1, q + cnt + 1);
  int l = 1, r = cnt;
  i64 res = 0;
  while (l <= r) {
    if (q[l] + q[r] <= ::w) res += r - l, l++;
    else r--;
  }
  return res;
}
i64 ans = 0;
void dfz(int u, int frm) {
  vis[u] = true, ans += calc(u, 0);
  for (auto [v, w] : adj[u]) {
    if (v == frm || vis[v]) continue;
    ans -= calc(v, w);
    sum = siz[v], rt = 0, max[rt] = 1e9;
    calcsiz(v, u), dfz(rt, u);
  }
}
void solve() {
  std::cin >> n;
  for (int i = 1, u, v, w; i < n; i++) {
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  std::cin >> w;
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