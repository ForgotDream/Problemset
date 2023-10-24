/**
 * @file    CF508D Tanya and Password.cpp
 * @author  ForgotDream
 * @brief   Euler Tour
 * @date    2023-09-04
 */
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50, base = 256;
int n, m, deg[2][N];
std::vector<int> adj[N];
char ch[10];
std::vector<char> ans;
void dfs(int u) {
  while (!adj[u].empty()) {
    int v = adj[u].back();
    adj[u].pop_back();
    dfs(v);
  }
  ans.push_back((char)(u % base));
  return;
}
inline void solve() {
  std::cin >> n;
  int maxn = 0, si = 0;
  for (int i = 1; i <= n; i++) {
    std::cin >> (ch + 1);
    int u = ch[1] * base + ch[2], v = ch[2] * base + ch[3];
    adj[u].push_back(v);
    deg[0][v]++, deg[1][u]++;
    maxn = std::max(maxn, std::max(u, v));
    si = u;
  }
  int cnt1 = 0, cnt2 = 0;
  for (int i = 0; i <= maxn; i++) {
    int delta = deg[0][i] - deg[1][i];
    if (delta == -1)
      cnt1++, si = i;
    else if (delta == 1)
      cnt2++;
    else if (delta != 0) {
      std::cout << "NO\n";
      return;
    }
  }
  if (cnt1 > 1 || cnt2 > 1 || cnt1 + cnt2 == 1) {
    std::cout << "NO\n";
    return;
  }
  dfs(si);
  ans.push_back((char)(si / base));
  if (ans.size() < n + 2) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";
    std::reverse(ans.begin(), ans.end());
    for (auto x : ans) std::cout << x;
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}