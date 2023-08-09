/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-08-08
 */
#include <bits/stdc++.h>
using i64 = long long;
using pii = std::pair<int, int>;
constexpr int N = 310, P = 16;
int n, m, t, a[N][N], sx, sy, p;
pii ed[P];
int enc[P];
int f[4][N][N], g[N * N];
std::vector<pii> adj[N * N];
int dis[P][N * N], val[P][N * N];
int dp1[1 << P][P], dp2[1 << P][P];
bool vis[N * N];
int encode(int i, int j) { return (i - 1) * m + j; }
pii decode(int i) { return std::make_pair(i / m + 1, i % m); }
void bfs(int s, int *dis, int *val, int siz = N * N) {
  std::queue<int> q;
  std::memset(dis, 0x3f, sizeof(int) * siz);
  std::memset(vis, 0, sizeof(vis));
  dis[s] = 0, val[s] = 0, q.push(s);
  vis[s] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto [v, w] : adj[u]) {
      if (!vis[v]) {
        dis[v] = dis[u] + 1;
        val[v] = val[u] + g[v];
        q.push(v), vis[v] = true;
      } else if (dis[v] == dis[u] + 1 && val[v] < val[u] + g[v]) {
        val[v] = val[u] + g[v];
        q.push(v);
      }
    }
  }
}
signed main() {
  freopen("expand.in", "r", stdin);
  freopen("expand.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m >> t;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) std::cin >> a[i][j];
  }
  std::cin >> sx >> sy >> p;
  sx++, sy++;
  for (int i = 1; i <= p; i++) {
    auto &[l, r] = ed[i];
    std::cin >> l >> r, l++, r++;
  }
  int lx[4] = {1, 1, n, n}, ly[4] = {1, m, 1, m};
  int rx[4] = {n, n, 1, 1}, ry[4] = {m, 1, m, 1};
  int dx[4] = {1, 1, -1, -1}, dy[4] = {1, -1, 1, -1};
  for (int k = 0; k < 4; k++) {
    for (int i = lx[k]; i != rx[k] + dx[k]; i += dx[k]) {
      for (int j = ly[k]; j != ry[k] + dy[k]; j += dy[k]) {
        if (a[i][j]) continue;
        f[k][i][j] = std::min({f[k][i - dx[k]][j], f[k][i][j - dy[k]],
                               f[k][i - dx[k]][j - dy[k]]}) +
                     1;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i][j]) continue;
      int cur = encode(i, j);
      g[cur] = std::min({f[0][i][j], f[1][i][j], f[2][i][j], f[3][i][j]}) - 1;
      g[cur] = std::min(t, g[cur]);
    }
  }
  dx[0] = 1, dx[1] = -1, dx[2] = 0, dx[3] = 0;
  dy[0] = 0, dy[1] = 0, dy[2] = 1, dy[3] = -1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i][j]) continue;
      for (int k = 0; k < 4; k++) {
        int cx = i + dx[k], cy = j + dy[k];
        if (a[cx][cy] || cx < 1 || cx > n || cy < 1 || cy > m) continue;
        adj[encode(i, j)].emplace_back(encode(cx, cy), 1);
      }
    }
  }
  ed[0] = std::make_pair(sx, sy);
  for (int i = 0; i <= p; i++) {
    enc[i] = encode(ed[i].first, ed[i].second);
    bfs(enc[i], dis[i], val[i]);
  }
  std::memset(dp1, 0x3f, sizeof(dp1));
  for (int i = 1; i <= p; i++) {
    dp1[1 << (i - 1)][i - 1] = dis[0][enc[i]];
    dp2[1 << (i - 1)][i - 1] = val[0][enc[i]];
  }
  for (int i = 0; i < 1 << p; i++) {
    for (int j = 0; j < p; j++) {
      if (!(i & (1 << j))) continue;
      for (int k = 0; k < p; k ++) {
        if (i & (1 << k)) continue;
        auto pre = dp1[i][j] + dis[j + 1][enc[k + 1]];
        if (dp1[i | (1 << k)][k] > pre) {
          dp1[i | (1 << k)][k] = pre;
          dp2[i | (1 << k)][k] = dp2[i][j] + val[j + 1][enc[k + 1]];
        } else if (dp1[i | (1 << k)][k] == pre &&
                   dp2[i | (1 << k)][k] < dp2[i][j] + val[j + 1][enc[k + 1]]) {
          dp2[i | (1 << k)][k] = dp2[i][j] + val[j + 1][enc[k + 1]];
        }
      }
    }
  }
  int ans1 = 0x3f3f3f3f, ans2 = 0;
  for (int i = 1; i <= p; i++) {
    if (dp1[(1 << p) - 1][i - 1] < ans1) {
      ans1 = dp1[(1 << p) - 1][i - 1];
      ans2 = dp2[(1 << p) - 1][i - 1];
    } else if (dp1[(1 << p) - 1][i - 1] == ans1) {
      ans2 = std::max(ans2, dp2[(1 << p) - 1][i - 1]);
    }
  }
  std::cout << ans1 << " " << ans2 + g[enc[0]] << "\n";
  return 0;
}