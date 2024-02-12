#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;

std::set<std::vector<int>> s;

int n;

int g[N];

int calc(int idx, int tim) {
  if (tim == 1) return g[idx];
  return calc(g[idx], tim - 1);
}

void dfs(int idx) {
  if (idx == n + 1) {
    std::vector<int> f;
    for (int i = 1; i <= n; i++) f.push_back(calc(i, n - 1));
    s.insert(f);
    return;
  }
  for (int i = 1; i <= n; i++) g[idx] = i, dfs(idx + 1);
}

void solve() {
  for (n = 2; n <= 8; n++) {
    s.clear();
    dfs(1);
    std::cout << s.size() << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
