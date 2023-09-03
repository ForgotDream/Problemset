/**
 * @file    CF547A Mike and Frog.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-31
 */
#include <iostream>
#include <set>

using i64 = long long;

constexpr int M = 1e6 + 50;
int h[2], a[2], x[2], y[2];
int m;
bool vis[2][M];
int cir[2], pos[2];
int nxt(int val, int d) { return (1ll * x[d] * val % m + y[d]) % m; }
void solve() {
  std::cin >> m;
  for (int i = 0; i < 2; i++) std::cin >> h[i] >> a[i] >> x[i] >> y[i];
  if (h[0] == a[0] && h[1] == a[1]) {
    std::cout << 0 << "\n";
    return;
  }
  vis[0][h[0]] = vis[1][h[1]] = true;
  int init;
  for (int i = 1; i <= m; i++) {
    h[0] = nxt(h[0], 0), h[1] = nxt(h[1], 1);
    if (h[0] == a[0] && h[1] == a[1]) {
      std::cout << i << "\n";
      return;
    }
    for (int j = 0; j < 2; j++) {
      if (vis[j][h[j]] && !vis[j][a[j]]) {
        std::cout << -1 << "\n";
        return;
      }
    }
    if (vis[0][h[0]] && vis[1][h[1]]) {
      init = i;
      for (int j = 0; j < 2; j++) {
        cir[j] = 0;
        if (h[j] == a[j]) pos[j] = 0;
        auto t = nxt(h[j], j);
        while (t != h[j]) {
          cir[j]++;
          if (t == a[j]) pos[j] = cir[j];
          t = nxt(t, j);
        }
      }
      break;
    }
    vis[0][h[0]] = vis[1][h[1]] = true;
  }
  cir[0]++, cir[1]++;
  std::set<int> s;
  for (i64 i = pos[0]; i; i += cir[0]) {
    if (s.find(i % cir[1]) != s.end()) {
      std::cout << -1 << "\n";
      return;
    } 
    s.insert(i % cir[1]);
    if (i % cir[1] == pos[1]) {
      std::cout << init + i << "\n";
      return;
    }
  }
  std::cout << -1 << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}