/**
 * @file    CF337D Book of Evil.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-21
 */
#include <cstring>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m, d, a[N];
std::vector<int> adj[N];
int f[N][2], max[N], semi[N];
bool used[N];

void dfs1(int u, int frm) {
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs1(v, u);
    if (f[v][1] != -1) f[u][1] = std::max(f[u][1], f[v][1] + 1);
    if (f[v][1] > f[max[u]][1]) semi[u] = max[u], max[u] = v;
    else if (f[v][1] > f[semi[u]][1]) semi[u] = v;
  }
  if (f[u][1] == -1 && used[u]) f[u][1] = 0;
}
void dfs2(int u, int frm) {
  int k = max[frm] == u ? semi[frm] : max[frm];
  if (f[k][1] != -1) f[u][0] = f[k][1] + 2;
  if (f[frm][0] != -1) f[u][0] = std::max(f[u][0], f[frm][0] + 1);
  if (f[u][0] == -1 && used[u]) f[u][0] = 0; 
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs2(v, u);
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m >> d;
  for (int i = 1; i <= m; i++) std::cin >> a[i], used[a[i]] = true;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  std::memset(f, -1, sizeof(f));
  dfs1(1, 0), dfs2(1, 0);

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (f[i][0] <= d && f[i][1] <= d) ans++;
  }
  std::cout << ans << "\n";

  return 0;
}