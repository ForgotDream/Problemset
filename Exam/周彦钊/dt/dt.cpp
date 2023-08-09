#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e5 + 50;
int n, m, a[N];
std::vector<int> adj[N];
struct Node {
  int idx = 0, val = 0;
  mutable i64 adjVal = 0;
  Node() = default;
  Node(int _i, i64 _a, int _v) { idx = _i, adjVal = _a, val = _v; }
  bool operator<(const Node &rhs) const {
    return adjVal < rhs.adjVal || (adjVal == rhs.adjVal && val > rhs.val) ||
           (adjVal == rhs.adjVal && val == rhs.val && idx < rhs.idx);
  }
};
std::set<Node> s;
i64 ans, cur[N];
bool del[N];
void dfs(int cnt, i64 cur) {
  if (cur > ans) return;
  for (int i = 1; i <= n; i++) {
    if (del[i]) continue;
    del[i] = true;
    i64 tmp = 0;
    for (auto v : adj[i]) {
      if (del[v]) continue;
      tmp += a[v];
    }
    dfs(cnt + 1, cur + tmp);
    del[i] = false;
  }
  if (cnt == n) ans = std::min(ans, cur);
}
signed main() {
  freopen("dt.in", "r", stdin);
  freopen("dt.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  if (n <= 10) {
    ans = 1e18;
    dfs(0, 0);
    std::cout << ans << "\n";
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    i64 tmp = 0;
    for (auto v : adj[i]) tmp += a[v];
    s.emplace(i, tmp, a[i]), cur[i] = tmp;
  }
  while (!s.empty()) {
    auto [idx, adjVal, val] = *s.begin();
    s.erase(s.begin());
    ans += adjVal, del[idx] = true;
    for (auto v : adj[idx]) {
      if (del[v]) continue;
      auto it = s.find(Node(v, cur[v], a[v]));
      it->adjVal -= val, cur[v] -= val;
    }
  }
  std::cout << ans << "\n";
  return 0;
}