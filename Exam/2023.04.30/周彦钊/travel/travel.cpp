#include <bits/stdc++.h>

using i64 = long long;

namespace Helper {
void useFileIO() {
  freopen("travel.in", "r", stdin);
  freopen("travel.out", "w", stdout);
  return;
}
};

int main() {
  Helper::useFileIO();

  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<bool>> reach(n + 1, std::vector<bool>(n + 1));
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    reach[u][v] = true;
  }

  for (int i = 1; i <= n; i++) {
    reach[i][i] = true;
  }

  // 传递闭包
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
      }
    }
  }

  int ans = 0;
  std::vector<int> v;
  for (int i = 0; i < (1 << n); i++) {
    int cur = i, cnt = 0;
    std::vector<bool> used(n + 1);

    for (int j = 0; (1 << j) <= cur; j++) {
      if (cur & (1 << j)) {
        used[j + 1] = true;
        cnt++;
      }
    }

    bool flg = true;
    for (int i = 1; i <= n; i++) {
      if (!used[i]) {
        continue;
      }
      for (int j = 1; j <= n; j++) {
        if (used[j] && i != j && (reach[i][j] || reach[j][i])) {
          flg = false;
          break;
        }
      }
    }

    if (flg && ans < cnt) {
      v.clear();
      ans = cnt;
      for (int i = 1; i <= n; i++) {
        if (used[i]) {
          v.push_back(i);
        }
      }
    }
  }

  std::cout << ans << "\n";
  for (int i = 0; i < ans; i++) {
    std::cout << v[i] << " \n"[i == ans - 1];
  }

  return 0;
}