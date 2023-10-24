#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 55;
int t, n, k;
int l[N], r[N], cnt[N];

void solve() {
  std::memset(cnt, 0, sizeof(cnt));
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> l[i] >> r[i];
  for (int i = 1; i <= n; i++) {
    for (int j = l[i]; j <= r[i]; j++) cnt[j]++;
  }
  for (int i = 1; i <= 50; i++) {
    if (i == k || cnt[i] < cnt[k]) continue;
    int cur = 0;
    for (int j = 1; j <= n; j++) {
      if (l[j] <= i && i <= r[j] && (l[j] > k || r[j] < k)) cur++;
    }
    if (cnt[i] - cur >= cnt[k]) {
      std::cout << "NO\n";
      return;
    }
  }
  std::cout << "YES\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> t;
  
  while (t--) solve();

  return 0;
}