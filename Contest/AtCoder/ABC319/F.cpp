#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 550;
int n, p[N], t[N], s[N], g[N];
std::vector<int> adj[N];
i64 f[N];
int idx[N], cnt;
void dfs(int u) {
  for (auto v : adj[u]) {

  }
}
void solve() {
  std::cin >> n;
  for (int i = 2; i <= n; i++) {
    std::cin >> p[i] >> t[i] >> s[i] >> g[i];
    if (t[i] == 2) idx[i] = ++cnt;
    adj[p[i]].push_back(i);
  }
  dfs(1);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}