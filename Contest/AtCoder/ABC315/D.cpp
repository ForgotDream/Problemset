#include <iostream>

using i64 = long long;

constexpr int N = 2050;
int h, w, A[N][N], ans;
bool del[N][N];

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> h >> w;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      char c;
      std::cin >> c;
      A[i][j] = c - 'a';
    }
  }

  return 0;
}