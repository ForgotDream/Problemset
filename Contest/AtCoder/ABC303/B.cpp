#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector a(m, std::vector<int>(n));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> a[i][j];
      a[i][j]--;
    }
  }

  std::vector flg(n, std::vector<int>(n));
  int ans = 0;
  for (int i = 0; i < n; i++) {
    flg[i][i] = true;
    for (int j = i + 1; j < n; j++) {
      for (int l = 0; l < m; l++) {
        for (int k = 0; k < n - 1; k++) {
          if (a[l][k] == i && a[l][k + 1] == j
            ||a[l][k] == j && a[l][k + 1] == i) {
            flg[i][j] = flg[j][i] = true;
            break;
          }
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (!flg[i][j] && !flg[j][i]) {
        ans++;
      }
    }
  }

  std::cout << ans << "\n";

  return 0;
}