#include <bits/stdc++.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>

using i64 = long long;
using f80 = long double;

int main() {
  freopen("brazil.in", "r", stdin);
  freopen("brazil.out", "w", stdout);
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  static const f80 EPS = 1e-7;
  
  int n, m;
  std::pair<int, int> door;
  std::cin >> door.first >> door.second >> n >> m;
  
  std::vector<std::pair<int, int>> a(n), b(m);
  for (auto &i : a) {
    std::cin >> i.first >> i.second;
  }
  for (auto &i : b) {
    std::cin >> i.first >> i.second;
  }
  a.push_back(door);
  
  auto getDis = [&](int i, int j) {
    return std::hypot(a[i].first - a[j].first, a[i].second - a[j].second);
  };
  
  std::vector<std::vector<f80>> dis(n + 1, std::vector<f80>(n + 1, 1e18));
  for (int i = 0; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      bool flg = true;
      for (int k = 0; k < m; k++) {
        if (b[k].first < std::min(a[i].first, a[j].first)) {
          continue;
        }
        if (b[k].first > std::max(a[i].first, a[j].first)) {
          continue;
        }
        if (b[k].second < std::min(a[i].second, a[j].second)) {
          continue;
        }
        if (b[k].second > std::max(a[i].second, a[j].second)) {
          continue;
        }
        
        auto getK = [&](std::pair<int, int> p, std::pair<int, int> q) {
          int x1 = p.first, x2 = q.first;
          int y1 = p.second, y2 = q.second;
          if (x1 == x2) {
            return f80(-1);
          }
          return f80(y1 - y2) / (x1 - x2);
        };
        
        if (getK(a[i], a[j]) == -1) {
          if (a[i].first == b[k].first) {
            flg = false;
            break;
          }
        } else {
          if (std::fabs(getK(b[k], a[i]) - getK(b[k], a[j])) <= EPS) {
            flg = false;
            break;
          }
        }
      }
      
      if (flg) {
        dis[i][j] = dis[j][i] = getDis(i, j) * (j == n ? 2 : 1);
      }
    }
  }
  
  for (int k = 0; k <= n; k++) {
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= n; j++) {
        dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
      }
    }
  }
  
  std::cout << i64(std::round(dis[0][n])) << "\n";
  
  return 0;
}
