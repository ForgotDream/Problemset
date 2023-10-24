#include <bits/stdc++.h>

using i64 = long long;

int dfs(int i, int j, std::vector<std::vector<int>> a, std::set<int> s, int h, int w) {
  if (s.count(a[i][j])) {
    return 0;
  }
  if (i == h - 1 && j == w - 1) {
    return 1;
  }
  s.insert(a[i][j]);
  int res = 0;

  if (i + 1 < h) {
    res += dfs(i + 1, j, a, s, h, w);
  } 
  if (j + 1 < w) {
    res += dfs(i, j + 1, a, s, h, w);
  }

  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int h, w;
  std::cin >> h >> w;

  std::vector<std::vector<int>> a(h, std::vector<int>(w));
  for (auto &i : a) {
    for (auto &j : i) {
      std::cin >> j;
    }
  }

  std::set<int> s;
  std::cout << dfs(0, 0, a, s, h, w) << "\n";

  return 0;
}