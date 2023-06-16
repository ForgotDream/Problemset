#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

int main() {
  freopen("graph.in", "r", stdin);
  freopen("graph.out", "w", stdout);

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<std::pair<int, int>>> adj(n);
  std::bitset<30001> bucket;
  bucket[0] = true;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    u--, v--;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
    bucket[w] = true;
  }

  int s, t;
  std::cin >> s >> t;
  s--, t--;

  auto check = [&](int lim) {
    std::vector<int> dis(n, inf);
    std::vector<bool> vis(n);
    std::priority_queue<
      std::pair<int, int>,
      std::vector<std::pair<int, int>>,
      std::greater<std::pair<int, int>>
    > pq;
    dis[s] = 0, pq.emplace(0, s);
    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();
      if (vis[u]) { continue; }
      vis[u] = true;
      for (auto i : adj[u]) {
        int v = i.first, w = i.second;
        if (dis[v] > dis[u] + w && w > lim) {
          dis[v] = dis[u] + w, pq.emplace(dis[v], v);
        }
      }
    }
    if (dis[t] == inf) { return std::make_pair(-1, -1); }
    std::vector<std::pair<int, int>> edges;
    std::vector<std::vector<int>> g(n);
    std::vector<int> pre(n);
    for (int u = 0; u < n; u++) {
      for (auto i : adj[u]) {
        int v = i.first, w = i.second;
        if (dis[v] == dis[u] + w) {
          edges.emplace_back(v, w), edges.emplace_back(u, w);
          g[u].push_back(edges.size() - 2), g[v].push_back(edges.size() - 1);
        }
      }
    }
    std::vector<std::pair<int, int>> fa(n, std::make_pair(-1, 0));
    // bfs
    [&]() {
      std::queue<int> q;
      std::fill(vis.begin(), vis.end(), false);
      q.emplace(s), vis[s] = true;
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto i : g[u]) {
          int v = edges[i].first, w = edges[i].second;
          if (vis[v]) { continue; }
          vis[v] = true, fa[v] = std::make_pair(u, w);
          q.push(v);
          if (v == t) { return; }
        }
      }
    }();
    int p = t;
    int max = -inf, min = inf, cnt = 0;
    while (p != s) {
      int w = fa[p].second;
      cnt++;
      max = std::max(max, w), min = std::min(min, w);
      p = fa[p].first;
    }
    if (cnt == 1) { return std::make_pair(-1, -1); }
    return std::make_pair(max, min);
  };

  if (!~check(0).first) {
    std::cout << "IMPOSSIBLE\n";
    return 0;
  }

  double tmp = inf;
  int ansMax, ansMin;
  for (int i = 0; i <= 30000; i++) {
    if (bucket[i]) {
      auto p = check(i);
      int max = p.first, min = p.second;
      if (max == -1 || min == -1) { continue; }
      if (1. * max / min < tmp) { ansMax = max, ansMin = min; }
    }
  }

  if (ansMax % ansMin == 0) {
    std::cout << ansMax / ansMin << "\n";
  } else {
    int g = std::__gcd(ansMax, ansMin);
    std::cout << (ansMax / g) << "/" << (ansMin / g) << "\n";
  }

  return 0;
}

/**
 * 正确性不显然，我觉得二分的更不显然
 * 时间复杂度 O(nm \log m)
 * 希望学校的机子能过！
 */