#include <algorithm>
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 5e5 + 50;
int n, m, d[N];
pii a[N];
std::vector<int> b;
int find(int u) {
  return std::lower_bound(b.begin(), b.end(), u) - b.begin() + 1;
}
void solve() {
  std::cin >> n >> m;
  b.clear(), b.push_back(1), b.push_back(m);
  for (int i = 1, l, r; i <= n; i++) {
    std::cin >> l >> r, a[i] = {l, r};
    b.push_back(l), b.push_back(r);
  }
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  int ans = 0;
  for (int i = 1; i <= b.size() + 1; i++) d[i] = 0;
  for (int i = 1; i <= n; i++) {
    auto [l, r] = a[i];
    if (l == 1) continue;
    l = find(l), r = find(r);
    d[l]++, d[r + 1]--;
  }
  for (int i = 1; i <= b.size() + 1; i++) d[i] += d[i - 1], ans = std::max(d[i], ans);
  for (int i = 1; i <= b.size() + 1; i++) d[i] = 0;
  for (int i = 1; i <= n; i++) {
    auto [l, r] = a[i];
    if (r == m) continue;
    l = find(l), r = find(r);
    d[l]++, d[r + 1]--;
  }
  for (int i = 1; i <= b.size() + 1; i++) d[i] += d[i - 1], ans = std::max(d[i], ans);
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
