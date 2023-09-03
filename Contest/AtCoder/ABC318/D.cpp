#include <iostream>

using i64 = long long;

constexpr int N = 20;
int n, a[N][N];
bool vis[N];
i64 cnt[1 << N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) std::cin >> a[i][j], a[j][i] = a[i][j];
  }
  for (int i = 0; i < 1 << n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i & (1 << (j - 1))) continue;
      for (int k = j + 1; k <= n; k++) {
        if (i & (1 << (k - 1))) continue;
        cnt[i ^ (1 << (j - 1)) ^ (1 << (k - 1))] =
            std::max(cnt[i] + a[j][k], cnt[i ^ (1 << (j - 1)) ^ (1 << (k - 1))]);
      }
    }
  }
  std::cout << cnt[(1 << n) - 1] << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}