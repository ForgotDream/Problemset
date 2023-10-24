#include <algorithm>
#include <iostream>
#include <set>
#include <queue>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;
int n, m, t[N], w[N], s[N];
std::set<int> cur;
std::set<pii> q;
i64 a[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) cur.insert(i);
  for (int i = 1; i <= m; i++) {
    std::cin >> t[i] >> w[i] >> s[i];
    while (!q.empty() && q.begin()->first <= t[i]) {
      cur.insert(q.begin()->second), q.erase(q.begin());
    }
    if (cur.empty()) continue;
    int u = *cur.begin();
    cur.erase(cur.begin());
    a[u] += w[i];
    q.emplace(t[i] + s[i], u);
  }
  for (int i = 1; i <= n; i++) std::cout << a[i] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}