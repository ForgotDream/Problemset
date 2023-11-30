#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 1e6 + 5;
int n, g;
std::vector<int> cir[N], adj[N];
int siz[N];
bool used[N];
void solve() {
  std::cin >> n >> g;
  std::set<std::pair<int, int>> st;
  used[1] = true;
  for (int i = 1; i <= g; i++) {
    std::cin >> siz[i];
    for (int j = 1, u; j <= siz[i]; j++) {
      std::cin >> u;
      if (u == 1) continue;
      cir[i].push_back(u), adj[u].push_back(i);
    }
    siz[i] = cir[i].size();
    if (siz[i]) st.emplace(siz[i], i);
  }
  while (true) {
    if (st.empty()) break;
    auto [_, pos] = *st.begin();
    st.erase(st.begin());
    if (siz[pos] > 1) break;
    siz[pos] = 0;
    for (auto u : cir[pos]) {
      if (used[u]) continue;
      used[u] = true;
      for (auto v : adj[u]) {
        if (siz[v] == 0) continue;
        st.erase(st.find({siz[v], v}));
        siz[v]--;
        if (siz[v] == 0) continue;
        st.emplace(siz[v], v);
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) ans += used[i];
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
