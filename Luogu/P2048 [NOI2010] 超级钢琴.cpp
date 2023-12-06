/**
 * @file    P2048 [NOI2010] 超级钢琴.cpp
 * @author  ForgotDream
 * @brief   Greedy + Heap + RMQ
 * @date    2023-12-03
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 5e5 + 50;
int n, k, l, r, a[N];
int f[N];
struct ST {
  int st[20][N];
  int cmp(int u, int v) { return a[u] > a[v] ? u : v; }
  void init() {
    for (int i = 1; i <= n; i++) st[0][i] = i;
    for (int i = 1; i <= std::__lg(n); i++) {
      for (int j = 1; j <= n - (1 << i) + 1; j++) {
        st[i][j] = cmp(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  int query(int l, int r) {
    int d = std::__lg(r - l + 1);
    return cmp(st[d][l], st[d][r - (1 << d) + 1]);
  }
} st;
struct Node {
  int l, r, p, idx;
  Node() = default;
  Node(int l, int r, int idx) : l(l), r(r), p(st.query(l, r)), idx(idx) {}
  bool operator<(const Node &rhs) const {
    return a[p] - a[idx - 1] < a[rhs.p] - a[rhs.idx - 1];
  }
};
void solve() {
  std::cin >> n >> k >> l >> r;
  for (int i = 1; i <= n; i++) std::cin >> a[i], a[i] += a[i - 1];
  st.init();
  std::priority_queue<Node> pq;
  for (int i = 1; i <= n; i++) {
    if (i + l - 1 > n) continue;
    pq.emplace(i + l - 1, std::min(i + r - 1, n), i);
  }
  i64 ans = 0;
  for (int i = 1; i <= k; i++) {
    auto [l, r, p, idx] = pq.top();
    pq.pop();
    ans += a[p] - a[idx - 1];
    if (l != p) pq.emplace(l, p - 1, idx);
    if (r != p) pq.emplace(p + 1, r, idx);
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
