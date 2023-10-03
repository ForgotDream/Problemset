#include <algorithm>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1050;
int n, k, a[N], b[N];
namespace DP_ON_SET {
void solve() {
  std::vector<std::vector<int>> f(n + 1, std::vector<int>(1 << k, -1));
  int mask = (1 << k) - 1, st = 0, t1 = 0, t2 = 0;
  for (int i = 1; i <= k; i++) {
    st += (a[i] << (i - 1));
    t1 += a[i] * b[i], t2 += (!a[i]) * b[i];
  }
  f[k][st] = t1, f[k][(~st) & mask] = t2;
  for (int i = k + 1; i <= n; i++) {
    for (int j = 0; j <= mask; j++) {
      int pre = (j & (mask >> 1)) << 1;
      for (int k = 0; k < 2; k++) {
        int cur = pre + k;
        if (f[i - 1][cur] != -1) f[i][j] = std::max(f[i][j], f[i - 1][cur]);
        int rev = (~cur) & mask;
        if (f[i - 1][rev] != -1) f[i][j] = std::max(f[i][j], f[i - 1][rev]);
      }
      if (j & (1 << (k - 1))) f[i][j] += b[i];
    }
  }
  int ans = 0;
  for (int i = 0; i <= mask; i++) {
    if (f[n][i] == -1) continue;
    ans = std::max(ans, f[n][i]);
  }
  std::cout << ans << "\n";
}
}  // namespace DP_ON_SET
namespace BRUTE_FORCE {
int tmp[N];
void solve() {
  int d = n - k + 1, mask = (1 << d) - 1;
  int ans = 0;
  for (int i = 0; i <= mask; i++) {
    std::copy(a + 1, a + n + 1, tmp + 1);
    for (int j = 1; j <= d; j++) {
      if (i & (1 << (j - 1))) {
        for (int l = j; l <= j + k - 1; l++) tmp[l] ^= 1;
      }
    }
    int cur = 0;
    for (int j = 1; j <= n; j++) cur += tmp[j] * b[j];
    ans = std::max(ans, cur);
  }
  std::cout << ans << "\n";
}
}  // namespace BRUTE_FORCE
void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) std::cin >> b[i];
  if (n <= 20 || k <= 10) DP_ON_SET::solve();
  else if (n - k <= 10) BRUTE_FORCE::solve();
}

int main() {
  std::freopen("challenge.in", "r", stdin);
  std::freopen("challenge.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
