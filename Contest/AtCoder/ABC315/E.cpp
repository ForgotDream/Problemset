#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;

constexpr int N = 2e5 + 50;
int N, C[N];
std::vector<int> adj[N], rev[N];
int deg[N], p[N], f[N], cnt;
bool vis[N];

void dfs(int u) {
  if (vis[u]) return;
  if (u != 1 && !vis[u]) p[++cnt] = u;
  vis[u] = true;
  for (auto v : rev[u]) dfs(v);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; i++) {
    std::cin >> C[i];
    for (int j = 1, u; j <= C[i]; j++) {
      std::cin >> u;
      adj[u].push_back(i), deg[i]++;
      rev[i].push_back(u);
    }
  }

  std::queue<int> q;
  for (int i = 1; i <= N; i++) {
    if (!deg[i]) q.push(i);
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : adj[u]) {
      f[v] = std::max(f[u] + 1, f[v]);
      if (!--deg[v]) q.push(v);
    }
  }

  dfs(1);
  std::sort(p + 1, p + cnt + 1, [&](int lhs, int rhs) {
    return f[lhs] < f[rhs] || (f[lhs] == f[rhs] && lhs < rhs);
  });
  for (int i = 1; i <= cnt; i++) std::cout << p[i] << " \n"[i == cnt];

  return 0;
}