#include <algorithm>
#include <iostream>
#include <numeric>

using i64 = long long;

constexpr int N = 2050, M = 11,  mod = 998244353;
int n, a[N], val[N], len[N];
int p[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    val[i] = a[i] % M;
    while (a[i]) len[i]++, a[i] /= 10;
  }
  std::iota(p + 1, p + n + 1, 1);
  i64 ans = 0;
  do {
    int cur = 0, tot = 0;
    for (int i = 1; i <= n; i++) {
      int pw = (tot & 1) ? 10 : 1;
      cur = (cur + 1ll * pw * val[p[i]] % M) % M;
      tot += len[p[i]];
    }
    ans += (cur == 0);
  } while (std::next_permutation(p + 1, p + n + 1));
  std::cout << ans << "\n";
}

int main() {
  std::freopen("eleven.in", "r", stdin);
  std::freopen("eleven.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
