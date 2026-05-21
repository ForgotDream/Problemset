#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

int n, q;
std::string s;

std::vector<int> adj[26];

void merge(int u, int v) {
  if (u == v) return;
  if (adj[u].size() < adj[v].size()) adj[u].swap(adj[v]);
  for (auto i : adj[v]) adj[u].push_back(i);
  adj[v].clear();
}

void solve() {
  std::cin >> n >> s;
  for (int i = 0; i < n; i++) adj[s[i] - 'a'].push_back(i);
  std::cin >> q;
  for (char u, v; q; q--) {
    std::cin >> v >> u;
    merge(u - 'a', v - 'a');
  }
  s.resize(n);
  for (int i = 0; i < 26; i++) {
    for (auto j : adj[i]) s[j] = i + 'a';
  }
  std::cout << s << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
