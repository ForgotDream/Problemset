#include <cstring>
#include <iostream>
#include <set>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50, K = 6;
int n, k, ans;
i64 v[K], a[N][K], b[N][K];
bool cmp(int u) {
  for (int i = 1; i <= k; i++) {
    if (v[i] < a[u][i]) return false;
  }
  return true;
}
void add(int u) {
  ans++;
  for (int i = 1; i <= k; i++) v[i] += b[u][i];
}
void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= k; i++) std::cin >> v[i];
  std::set<int> s;
  for (int i = 1; i <= n; i++) s.insert(i);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= k; j++) std::cin >> a[i][j];
    for (int j = 1; j <= k; j++) std::cin >> b[i][j];
  }
  ans = 0;
  for (int _ = 1; _ <= n; _++) {
    bool flg = false;
    std::vector<int> defeated;
    for (auto i : s) {
      if (cmp(i)) flg = true, add(i), defeated.push_back(i);
    }
    for (auto i : defeated) s.erase(i);
    if (!flg) break;
  }
  std::cout << ans << "\n";
  for (int i = 1; i <= k; i++) std::cout << v[i] << " \n"[i == k];
}

int main() {
  std::freopen("tower.in", "r", stdin);
  std::freopen("tower.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
