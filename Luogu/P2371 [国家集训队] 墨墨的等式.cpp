/*
 * @file    P2371 [国家集训队] 墨墨的等式.cpp
 * @author  ForgotDream
 * @brief   同余最短路
 * @date    2024-01-22
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using pii = std::pair<int, int>;

constexpr int N = 5e5 + 50, M = 15;

int n, a[M], mn;
i64 l, r;

std::vector<pii> adj[N];
i64 dis[N];
bool ins[N];

i64 query(i64 u) {
  i64 res = 0;
  for (int i = 0; i < mn; i++) {
    if (u >= dis[i]) res += (u - dis[i]) / mn + 1;
  }
  return res;
}

void solve() {
  std::cin >> n >> l >> r;
  int m = 0;
  for (int i = 1, u; i <= n; i++) {
    std::cin >> u;
    if (u) a[++m] = u;
  }

  mn = *std::min_element(a + 1, a + m + 1);
  for (int i = 0; i < mn; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[j] == i) continue;
      adj[i].emplace_back((i + a[j]) % mn, a[j]);
    }
  }

  memset(dis, 0x3f, sizeof(dis));
  std::queue<int> q;

  dis[0] = 0, ins[0] = true, q.push(0);
  while (!q.empty()) {
    int u = q.front();
    q.pop(), ins[u] = false;
    for (auto [v, w] : adj[u]) {
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        if (!ins[v]) q.push(v), ins[v] = true;
      }
    }
  }

  std::cout << query(r) - query(l - 1) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
