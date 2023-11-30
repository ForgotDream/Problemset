/**
 * @file    P3264 [JLOI2015] 管道连接.cpp
 * @author  ForgotDream
 * @brief   Steiner Tree
 * @date    2023-11-29
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using pii = std::pair<int, int>;

constexpr int N = 1050, P = 11, inf = 0x3f3f3f3f;
int n, m, p;
pii a[N];
int col[N];
std::vector<pii> adj[N];
int f[1 << P][N], g[1 << P];
bool ins[N];
void spfa(int st) {
  memset(ins, false, sizeof(ins));
  std::queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (f[st][i] != inf) q.push(i), ins[i] = true;
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop(), ins[u] = false;
    for (auto [v, w] : adj[u]) {
      if (f[st][v] > f[st][u] + w) {
        f[st][v] = f[st][u] + w;
        if (!ins[v]) q.push(v);
      }
    }
  }
}
int calc(int cnt) {
  int mask = (1 << cnt) - 1;
  for (int st = 1; st <= mask; st++) {
    for (int nxt = st & (st - 1); nxt; nxt = (nxt - 1) & st) {
      if (nxt < (st ^ nxt)) break;
      for (int i = 1; i <= n; i++) {
        f[st][i] = std::min(f[st][i], f[nxt][i] + f[st ^ nxt][i]);
      }
    }
    spfa(st);
  }
  return *std::min_element(f[mask] + 1, f[mask] + n + 1);
}
void solve() {
  std::cin >> n >> m >> p;
  for (int i = 1, u, v, w; i<= m; i++) {
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
  }
  for (int i = 1; i <= p; i++) std::cin >> a[i].first >> a[i].second;
  std::sort(a + 1, a + p + 1);
  int colCnt = 0;
  for (int i = 1; i <= p; i++) {
    if (a[i].first != a[i - 1].first) colCnt++;
    col[i] = colCnt - 1;
  }
  for (int i = 1; i <= p; i++) a[i].first = col[i];
  memset(g, 0x3f, sizeof(g));
  int mask = (1 << colCnt) - 1;
  for (int st = 1; st <= mask; st++) {
    int t = 0;
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= p; i++) {
      if (st & (1 << a[i].first)) f[1 << t++][a[i].second] = 0;
    }
    g[st] = calc(t);
  }
  for (int st = 1; st <= mask; st++) {
    for (int nxt = st & (st - 1); nxt; nxt = (nxt - 1) & st) {
      if (nxt < (st ^ nxt)) break;
      g[st] = std::min(g[st], g[nxt] + g[st ^ nxt]);
    }
  }
  std::cout << g[mask] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
