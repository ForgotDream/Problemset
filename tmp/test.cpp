// Problem: #6490. 「XXOI 2018」暑假时在做什么？有没有空？可以来学物理吗？
// Contest: LibreOJ
// URL: https://loj.ac/p/6490
// Memory Limit: 256 MB
// Time Limit: 400 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
typedef long long ll;
const ll INF = 1e18;

const int maxn = 1e5 + 5;
int n, L, R, a[maxn];
ll sum[maxn], f[maxn];

namespace ST {
int lg[maxn];
ll f[maxn][20], dp[maxn][20];

void init() {
  for (int i = 0; i <= n; ++i) f[i][0] = dp[i][0] = sum[i];
  for (int i = 2; i <= n + 1; ++i) lg[i] = lg[i >> 1] + 1;
  for (int k = 1; (1 << k) <= n; ++k) {
    for (int i = 0; i + (1 << k) - 1 <= n; ++i) {
      f[i][k] = std::max(f[i][k - 1], f[i + (1 << (k - 1))][k - 1]);
      dp[i][k] = std::min(dp[i][k - 1], dp[i + (1 << (k - 1))][k - 1]);
    }
  }
  return;
}

ll RMQmax(int l, int r) {
  if (l > r) return -INF;
  int k = lg[r - l + 1];
  return std::max(f[l][k], f[r - (1 << k) + 1][k]);
}

ll RMQmin(int l, int r) {
  if (l > r) return INF;
  int k = lg[r - l + 1];
  return std::min(dp[l][k], dp[r - (1 << k) + 1][k]);
}
}  // namespace ST

void solve(int l, int r) {
  if (r - l + 1 < L) return;
  if (l == r) {
    if (L == 1) f[l] = std::max(f[l], (ll)a[l]);
    return;
  }

  int mid = (l + r) >> 1;
  solve(l, mid);
  solve(mid + 1, r);

  ll pre = -INF, suf = -INF;
  for (int i = l; i <= mid; ++i) {
    int x = i + L - 1, y = i + R - 1;
    pre = std::max(
        pre, ST::RMQmax(std::max(x, mid + 1), std::min(y, r)) - sum[i - 1]);
    f[i] = std::max(f[i], pre);
  }

  for (int i = r; i > mid; --i) {
    int x = i - R + 1, y = i - L + 1;
    suf = std::max(
        suf, sum[i] - ST::RMQmin(std::max(x, l) - 1, std::min(y, mid) - 1));
    f[i] = std::max(f[i], suf);
  }

  return;
}

int main() {
  scanf("%d %d %d", &n, &L, &R);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]), sum[i] = sum[i - 1] + a[i], f[i] = -INF;

  ST::init();

  solve(1, n);

  for (int i = 1; i <= n; ++i) printf("%lld ", f[i]);
  return 0;
}
