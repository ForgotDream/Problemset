#include <bits/stdc++.h>

using i64 = long long;

constexpr int M = 101;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  
  std::vector a(n, std::vector<std::tuple<int, int, int>>(2));
  std::vector dim(3, std::vector<std::vector<std::tuple<int, int, int, int>>>(M));
  for (int i = 0; i < n; i++) {
    auto &[x1, y1, z1] = a[i][0];
    auto &[x2, y2, z2] = a[i][1];
    std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
    dim[0][x1].emplace_back(y1, z1, y2, z2);
    dim[1][y1].emplace_back(x1, z1, x2, z2);
    dim[2][z1].emplace_back(x1, y1, x2, y2);
    dim[0][x2].emplace_back(y1, z1, y2, z2);
    dim[1][y2].emplace_back(x1, z1, x2, z2);
    dim[2][z2].emplace_back(x1, y1, x2, y2);
  }

  std::vector<std::set<int>> ans(n);

  auto cal = [&](int d1, int d2) {
    for (int i = 0; i < n; i++) {
      
    }
  };

  for (int i = 0; i < 3; i++) {
    for (int j = i + 1; j < 3; j++) {

    }
  }

  return 0;
}