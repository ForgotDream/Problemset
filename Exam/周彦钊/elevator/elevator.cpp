#include <bits/stdc++.h>

using i64 = long long;

int main() {  
  freopen("elevator.in", "r", stdin);
  freopen("elevator.out", "w", stdout);

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  i64 k;
  std::cin >> n >> k;

  auto rolling = [&](int &i, int &j) {
    int t = i;
    i = j, j = n - t - 1;
  };

  std::vector<i64> st;
  int m = n * n / 4;
  std::vector<int> t(m);
  std::function<void(int)> dfs = [&](int cur = 0) {
    if (cur == m) {
      i64 res = 0;
      for (int i = 0; i < m; i++) {
        int curx = i / (n / 2), cury = i % (n / 2);
        for (int j = 0; j < t[i]; j++) {
          rolling(curx, cury);
        }
        res |= 1ll << (n * n - (curx * n + cury) - 1);
      }
      st.push_back(res);
      return;
    }
    for (int i = 0; i < 4; i++) {
      t[cur] = i;
      dfs(cur + 1);
    }
  };

  dfs(0);
  std::sort(st.begin(), st.end());

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << !!(st[k - 1] & (1 << (n * n - (i * n + j) - 1)));
    }
    std::cout << "\n";
  }

  return 0;
}