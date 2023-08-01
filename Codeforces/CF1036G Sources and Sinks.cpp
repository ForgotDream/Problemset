/**
 * @file    CF1036G Sources and Sinks.cpp
 * @author  ForgotDream
 * @brief   Topo + Ad Hoc
 * @date    2023-08-01
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 50, K = 22;
int n, m;
std::vector<int> adj[N];
int in[N], out[N], encodeS[N], encodeT[N];
bool vis[N];
std::bitset<K> reach[K];

std::bitset<K> topo(int s) {
  std::bitset<K> res;
  std::queue<int> q;
  std::memset(vis, 0, sizeof(vis)), q.push(s);
  if (encodeT[s]) res.set(encodeT[s]);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : adj[u]) {
      if (encodeT[v]) res.set(encodeT[v]);
      if (!vis[v]) q.push(v), vis[v] = true;
    }
  }
  return res;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v;
    std::cin >> u >> v;
    adj[u].push_back(v);
    out[u]++, in[v]++;
  }

  std::vector<int> s, t;
  for (int i = 1; i <= n; i++) {
    if (!in[i]) s.push_back(i), encodeS[i] = s.size();
    if (!out[i]) t.push_back(i), encodeT[i] = t.size();
  }
  for (auto i : s) reach[encodeS[i]] = topo(i);

  int k = s.size();
  for (int i = 1; i < (1 << k) - 1; i++) {
    std::bitset<K> f;
    int cnt = 0;
    for (int j = 0; j < s.size(); j++) {
      if (i & (1 << j)) f |= reach[j + 1], cnt++;
    }
    if (cnt >= f.count()) {
      std::cout << "NO\n";
      return 0;
    }
  }
  std::cout << "YES\n";

  return 0;
}
