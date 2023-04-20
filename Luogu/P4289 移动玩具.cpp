/**
 * @file    P4289 移动玩具.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-04-02
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

signed main() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int s = 0, t = 0;
  for (int i = 0; i < 16; i++) {
    char c;
    std::cin >> c;
    s += (c == '1') << i;
  }
  for (int i = 0; i < 16; i++) {
    char c;
    std::cin >> c;
    t += (c == '1') << i;
  }

  if (s == t) {
    std::cout << 0 << "\n";
    return 0;
  }

  std::queue<int> q;
  std::vector<int> dis(1 << 16, -1);

  q.push(s);
  dis[s] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int i = 0; i < 16; i++) {
      if ((u & (1 << i)) == 0) {
        continue;
      }

      if (i / 4 != 0) {
        if (!(u & (1 << (i - 4)))) {
          int v = u + (1 << (i - 4)) - (1 << i);
          if (dis[v] == -1) {
            q.push(v);
            dis[v] = dis[u] + 1;
            if (v == t) {
              std::cout << dis[v] << "\n";
              return 0;
            }
          }
        }
      }

      if (i / 4 != 3) {
        if (!(u & (1 << (i + 4)))) {
          int v = u + (1 << (i + 4)) - (1 << i);
          if (dis[v] == -1) {
            q.push(v);
            dis[v] = dis[u] + 1;
            if (v == t) {
              std::cout << dis[v] << "\n";
              return 0;
            } 
          } 
        }
      }

      if ((i % 4) != 0) {
        if (!(u & (1 << (i - 1)))) {
          int v = u + (1 << (i - 1)) - (1 << i);
          if (dis[v] == -1) {   
            q.push(v);
            dis[v] = dis[u] + 1;
            if (v == t) {
              std::cout << dis[v] << "\n";
              return 0;
            }
          }
        }
      }

      if ((i % 4) != 3) {
        if (!(u & (1 << (i + 1)))) {
          int v = u + (1 << (i + 1)) - (1 << i);
          if (dis[v] == -1) {
            q.push(v);
            dis[v] = dis[u] + 1;
            if (v == t) {
              std::cout << dis[v] << "\n";
              return 0;
            }    
          }
        }
      }
    }
  }

  return 0;
}