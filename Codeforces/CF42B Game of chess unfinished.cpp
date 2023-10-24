/**
 * @file    CF42B Game of chess unfinished.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-09-03
 */
#include <iostream>

using i64 = long long;

constexpr int N = 10;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1},  {0, -1},
                        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
char a[10][10];
int x[N], y[N];
bool mat[N][N];
int atk[N][N];
bool valid(int x, int y) { return 1 <= x && x <= 8 && 1 <= y && y <= 8; }
void solve() {
  for (int i = 0; i < 4; i++) {
    std::cin >> a[i];
    x[i] = a[i][0] - 'a' + 1, y[i] = a[i][1] - '0';
    std::cerr << x[i] << " " << y[i] << "\n";
    if (i != 3) mat[x[i]][y[i]] = true;
  }
  for (int i = 0; i < 2; i++) {
    atk[x[i]][y[i]]++;
    for (int k = 0; k < 4; k++) {
      int dx = x[i] + d[k][0], dy = y[i] + d[k][1];
      while (valid(dx, dy) && !mat[dx][dy]) {
        atk[dx][dy]++, dx += d[k][0], dy += d[k][1];
      }
      if (valid(dx, dy)) atk[dx][dy]++;
    }
  }
  for (int i = 0; i < 8; i++) atk[x[2] + d[i][0]][y[2] + d[i][1]]++;
  atk[x[2]][y[2]]++;
  for (int i = 1; i <= 8; i++) {
    for (int j = 1; j <= 8; j++) std::cerr << atk[i][j] << " \n"[j == 8];
  }
  if (!atk[x[3]][y[3]]) {
    std::cout << "OTHER\n";
    return;
  }
  for (int i = 0; i < 8; i++) {
    if (!valid(x[3] + d[i][0], y[3] + d[i][1])) continue;
    if (!atk[x[3] + d[i][0]][y[3] + d[i][1]]) {
      std::cout << "OTHER\n";
      return;
    } else if (atk[x[3] + d[i][0]][y[3] + d[i][1]] == 1 &&
               mat[x[3] + d[i][0]][y[3] + d[i][1]]) {
      std::cout << "OTHER\n";
      return;
    }
  }
  std::cout << "CHECKMATE\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}