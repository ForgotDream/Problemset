#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;

constexpr int N = 105;
int n, m, a[N][N], deg[N];
std::vector<int> adj[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= m; i++) adj[i].clear(), deg[i] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) std::cin >> a[i][j];
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) {
        if (a[j][i] > a[k][i]) adj[j].push_back(k), deg[k]++;
      }
    }
  }
  std::queue<int> q;
  for (int i = 1; i <= m; i++) {
    if (!deg[i]) q.push(i);
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : adj[u]) {
      if (!--deg[v]) q.push(v);
    }
  }
  for (int i = 1; i <= m; i++) {
    if (deg[i]) {
      std::cout << "NO\n";
      return;
    }
  }
  std::cout << "YES\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
