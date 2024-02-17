#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 5050;

int n, m, U[N], V[N];
int w[N];
i64 f[N];

std::vector<int> adj[N];
int deg[N];

void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= m; i++) std::cin >> U[i] >> V[i];
  for (int i = 1; i <= n; i++) std::cin >> w[i];
  for (int i = 1; i <= n; i++) std::cin >> f[i];

  for (int i = 1; i <= m; i++) {
    if (w[U[i]] > w[V[i]]) {
      adj[U[i]].push_back(V[i]);
      deg[V[i]]++;
    } else if (w[U[i]] < w[V[i]]) {
      adj[V[i]].push_back(U[i]);
      deg[U[i]]++;
    }
  }

  std::queue<int> q;
  for (int i = 1; i <= n; i++) if (!deg[i]) q.push(i);

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : adj[u]) {
      f[v] += f[u];
      if (!--deg[v]) q.push(v);
    }
  }

  for (int i = 1; i <= n; i++) {
    std::cerr << f[i] << "\n";
  }
  std::cout << std::accumulate(f + 1, f + n + 1, 0) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
