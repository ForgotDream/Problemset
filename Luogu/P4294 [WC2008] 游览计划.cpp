/*
 * @file    P4294 [WC2008] 游览计划.cpp
 * @author  ForgotDream
 * @brief   Steiner Tree
 * @date    2024-01-22
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using pii = std::pair<int, int>;

inline bool chkmin(int &x, const int &y) { return x > y ? x = y, true : false; }

constexpr int N = 105, K = 10, inf = 0x3f3f3f3f;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int n, m, k;
int a[N][N], p[K];

inline int enc(int x, int y) { return x * m + y; }
inline int enc(pii c) { return c.first * m + c.second; }
inline pii dec(int i) { return {i / m, i % m}; }
inline bool valid(int x, int y) { return 0 <= x && x < n && 0 <= y && y < m; }

int f[1 << K][N];
pii pre[1 << K][N];
bool vis[N];

void dijkstra(int st) {
  memset(vis, false, sizeof(vis));
  std::priority_queue<pii, std::vector<pii>, std::greater<>> pq;

  for (int i = 0; i < n * m; i++) if (f[st][i] != inf) pq.emplace(f[st][i], i);
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) continue;
    vis[u] = true;
    auto [x, y] = dec(u);
    for (int i = 0; i < 4; i++) {
      int dx = x + d[i][0], dy = y + d[i][1], v = enc(dx, dy);
      if (valid(dx, dy) && f[st][v] > f[st][u] + a[dx][dy]) {
        f[st][v] = f[st][u] + a[dx][dy];
        pre[st][v] = {st, u};
        pq.emplace(f[st][v], v);
      }
    }
  }
}

int ans[K][K];
void dfs(int st, pii u) {
  if (!pre[st][enc(u)].first) return;
  // std::cerr << pre[st][enc(u)].first << " " << pre[st][enc(u)].second << "\n";
  ans[u.first][u.second] = 1;
  if (pre[st][enc(u)].second == enc(u)) dfs(st ^ pre[st][enc(u)].first, u);
  dfs(pre[st][enc(u)].first, dec(pre[st][enc(u)].second));
}

void solve() {
  std::cin >> n >> m;

  memset(f, 0x3f, sizeof(f));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> a[i][j];
      if (!a[i][j]) p[k++] = enc(i, j);
    }
  }

  if (k == 0) {
    std::cout << 0 << "\n";
    for (int i = 0; i < n; i++) std::cout << std::string(m, '_') << "\n";
    return;
  }

  int mask = (1 << k) - 1;
  for (int i = 0; i < k; i++) f[1 << i][p[i]] = 0;

  for (int st = 1; st <= mask; st++) {
    for (int sub = st & (st - 1); sub; sub = (sub - 1) & st) {
      if (sub < (sub ^ st)) break;
      for (int i = 0; i < n * m; i++) {
        auto [x, y] = dec(i);
        if (chkmin(f[st][i], f[sub][i] + f[sub ^ st][i] - a[x][y])) {
          pre[st][i] = {sub, i};
        }
      }
    }
    dijkstra(st);
  }

  std::cout << f[mask][p[0]] << "\n";
  dfs(mask, dec(p[0]));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i][j] == 0) std::cout << 'x';
      else std::cout << (ans[i][j] ? 'o' : '_');
    }
    std::cout << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
