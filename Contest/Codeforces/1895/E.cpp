#include <iostream>

using i64 = long long;

constexpr int N = 3e5 + 50;
int n, ax[N], ay[N], bx[N], by[N];
int f[2][N];
bool vis[2][N];
int dfs(int p, int u) {
  if (vis[p][u]) return f[p][u];
  vis[p][u] = true;
  
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> ax[i];
  for (int i = 1; i <= n; i++) std::cin >> ay[i];
  for (int i = 1; i <= n; i++) std::cin >> bx[i];
  for (int i = 1; i <= n; i++) std::cin >> by[i];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}