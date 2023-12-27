/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-12-27
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e4 + 50;
int n, m;
struct Edge {
  int u, v, w1, w2;
};

struct LCT {
  int ch[N][2], siz[N], tag[N], fa[N];
  inline void pushup(int u) { siz[u] = siz[ch[u][0]] + siz[ch[u][1]] + 1; }
  inline void pushdown([[__maybe_unused__]] int u) {
    // todo
  }
  inline bool check(int u) { return fa[ch[u][1]] == u; }
  inline void rotate(int u) {

  }
} lct;

void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v, w1, w2; i <= m; i++) {
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
