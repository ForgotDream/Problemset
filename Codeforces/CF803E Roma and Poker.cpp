/**
 * @file    CF803E Roma and Poker.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-11-01
 */
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 1050;
int n, k;
char s[N];
std::vector<pii> adj[N];
bool vis[N];
int cnt[N], dis[N];
inline void add(int u, int v, int w) { adj[u].emplace_back(v, w); }
bool spfa(int s) {
  std::memset(dis, 0x3f, sizeof(dis));
  std::memset(cnt, 0, sizeof(cnt));
  std::memset(vis, false, sizeof(vis));
  std::queue<int> q;
  q.push(s), dis[s] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop(), vis[u] = false;
    for (auto [v, w] : adj[u]) {
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        if (!vis[v]) {
          if (++cnt[v] > n) return false;
          vis[v] = true, q.push(v);
        }
      }
    }
  }
  return true;
}
void solve() {
  std::cin >> n >> k >> (s + 1);
  for (int i = 1; i <= n; i++) {
    if (s[i] == '?') add(i, i - 1, 1), add(i - 1, i, 1);
    else if (s[i] == 'W') add(i, i - 1, -1), add(i - 1, i, 1);
    else if (s[i] == 'L') add(i, i - 1, 1), add(i - 1, i, -1);
    else add(i, i - 1, 0), add(i - 1, i, 0);
    if (i != n) add(0, i, k - 1), add(i, 0, k - 1);
  }
  add(0, n, k), add(n, 0, -k);
  if (spfa(0)) {
    for (int i = 1; i <= n; i++) {
      int d = dis[i] - dis[i - 1];
      if (d == 1) std::cout << 'W';
      else if (d == 0) std::cout << 'D';
      else std::cout << 'L';
    }
    std::cout << "\n";
    return;
  }
  adj[0].erase(adj[0].rbegin().base()), adj[n].erase(adj[n].rbegin().base());
  add(0, n, -k), add(n, 0, k);
  if (spfa(0)) {
    for (int i = 1; i <= n; i++) {
      int d = dis[i] - dis[i - 1];
      if (d == 1) std::cout << 'W';
      else if (d == 0) std::cout << 'D';
      else std::cout << 'L';
    }
    std::cout << "\n";
    return;
  }
  std::cout << "NO\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
