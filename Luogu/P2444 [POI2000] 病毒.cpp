/**
 * @file    P2444 [POI2000] 病毒.cpp
 * @author  ForgotDream
 * @brief   ACAM
 * @date    2023-09-01
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using i64 = long long;

namespace ACAM {
constexpr int N = 1e6 + 50, SIG = 2;
struct Acam {
  int tr[N][SIG], nxt[N], end[N], cnt;
  bool valid[N];
  int convert(char c) { return c - '0'; }
  int insert(std::string s) {
    int p = 0;
    for (auto c : s) {
      int d = convert(c);
      if (!tr[p][d]) tr[p][d] = ++cnt;
      p = tr[p][d];
    }
    end[p]++, valid[p] = true;
    return p;
  }
  void build() {
    std::queue<int> q;
    for (int i = 0; i < SIG; i++) {
      if (tr[0][i]) q.push(tr[0][i]);
    }
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < SIG; i++) {
        if (!tr[u][i]) {
          tr[u][i] = tr[nxt[u]][i];
        } else {
          nxt[tr[u][i]] = tr[nxt[u]][i], q.push(tr[u][i]);
          valid[tr[u][i]] |= valid[nxt[tr[u][i]]];
        }
      }
    }
  }
  bool ins[N], vis[N];
  void dfs(int u) {
    if (ins[u]) {
      std::cout << "TAK\n";
      exit(0);
    }
    ins[u] = true, vis[u] = true;
    for (int i = 0; i < SIG; i++) {
      int v = tr[u][i];
      if (valid[v] || (vis[v] && !ins[v])) continue;
      dfs(v);
    }
    ins[u] = false;
  }
} acam;
}  // namespace ACAM
int n;
std::string s;
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> s, ACAM::acam.insert(s);
  ACAM::acam.build();
  ACAM::acam.dfs(0);
  std::cout << "NIE\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}