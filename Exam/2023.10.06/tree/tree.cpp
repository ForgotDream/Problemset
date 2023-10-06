#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;
int n, m;
pii a[N];
int ans[N], cnt[N];
std::set<int> st;
void solve() {
  std::memset(ans, 0, sizeof(ans)), std::memset(cnt, 0, sizeof(cnt));
  st.clear();
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) st.insert(i);
  for (int i = 1; i <= m; i++) std::cin >> a[i].first >> a[i].second;
  for (int i = m + 1; i <= m + n; i++) a[i] = std::make_pair(i - m, i - m);
  std::sort(a + 1, a + m + n + 1);
  int s = 1, t = 0;
  for (int _ = 1; _ <= m + n; _++) {
    auto [l, r] = a[_];
    if (r <= t) continue;
    while (s < l) {
      cnt[ans[s]]--;
      if (!cnt[ans[s]]) st.insert(ans[s]);
      s++;
    }
    for (int i = t + 1; i <= r; i++) {
      if (ans[i]) continue;
      ans[i] = *st.begin(), cnt[*st.begin()]++;
      st.erase(st.begin());
    }
    t = r;
  }
  for (int i = 1; i <= n; i++) std::cout << ans[i] << " \n"[i == n];
  // for (int i = 1; i <= n; i++) std::cout << ans[i] << " ";
}

int main() {
  std::freopen("tree.in", "r", stdin);
  std::freopen("tree.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
