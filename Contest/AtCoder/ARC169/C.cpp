#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 5050, mod = 998244353;
int n, a[N], sum[N][N];
i64 f[N][N], g[N][N];
struct BIT {
  i64 tree[N];
  void modify(int u, i64 val) {
    for (int i = u; i <= n; i += i & -i) tree[i] += val;
  }
  i64 query(int u) {
    i64 res = 0;
    for (int i = u; i; i -= i & -i) res += tree[i];
    return res;
  }
  i64 query(int l, int r) { return query(r) - query(l - 1); }
} bit[N];
inline int getSum(int l, int r, int v) {
  return sum[r][v] - sum[l - 1][v];
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    for (int j = 0; j <= n; j++) sum[i][j] = sum[i - 1][j];
    if (a[i] != -1) sum[i][a[i]]++, sum[i][0]++;
  }
  if (a[1] == -1) {
    for (int i = 1; i <= n; i++) f[1][i] = g[1][i] = 1;
  } else {
    f[1][a[1]] = g[1][a[1]] = 1;
  }
  for (int i = 2; i <= n; i++) {
    if (a[i] == -1) {
      for (int j = 1; j <= n; j++) {

      }
    } else {
      int lo = 1, hi = std::min(i, a[i]), len = 1;
      while (lo <= hi) {
        int mid = (lo + hi) >> 1, l = i - mid + 1, r = i;
        if (getSum(l, r, 0) != getSum(l, r, a[i])) hi = mid - 1;
        else lo = mid + 1, len = mid;
      }
      f[i][a[i]] = g[i - 1][a[i]] - g[i - len - 1][a[i]] - bit[a[i]].query(i - len, i - 1);
      bit[a[i]].modify(i, f[i][a[i]]);
    }
    for (int j = 1; j <= n; j++) g[i][j] = g[i - 1][j] + f[i][j];
  }
  i64 ans = 0;
  for (int i = 1; i <= n; i++) ans = (ans + f[n][i]) % mod;
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
