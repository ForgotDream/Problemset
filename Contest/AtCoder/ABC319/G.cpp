#include <iostream>
#include <set>
#include <queue>
#include <vector>

using i64 = long long;

constexpr int N = 2e5 + 50, mod = 998244353;
int n, m;
std::set<int> s, adj[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].insert(v), adj[v].insert(u);
  }
  std::queue<int> q;
  q.push(1);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}