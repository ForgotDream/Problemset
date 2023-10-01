#include <algorithm>
#include <bitset>
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50, M = 350;
int n, m, q;
int a[N], b[N];
std::bitset<N> acnt, bcnt, ans;
void solve() {
  std::cin >> n >> m >> q;
  int max = 0;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    acnt[a[i]] = acnt[a[i]] ^ true;
    max = std::max(max, a[i]);
  }
  for (int i = 1; i <= m; i++) {
    std::cin >> b[i];
    bcnt[b[i]] = bcnt[b[i]] ^ true;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= M; j++) ans[a[i] % j] = ans[a[i] % j] ^ bcnt[j];
  }
  std::bitset<N> mask;
  for (int i = 1; i <= m; i++) {
    if (b[i] <= M) continue;
    mask.set(), mask >>= N - b[i];
    for (int j = 0; b[i] * j <= max; j++) {
      ans ^= mask & (acnt >> b[i] * j);
    }
  }
  for (int k; q; q--) std::cin >> k, std::cout << ans[k] << "\n";
}

int main() {
  std::freopen("magician.in", "r", stdin);
  std::freopen("magician.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
