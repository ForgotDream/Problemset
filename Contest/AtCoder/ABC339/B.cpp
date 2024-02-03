#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 105;
constexpr int d[][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int h, w, n;
int col[N][N];

void solve() {
  std::cin >> h >> w >> n;
  
  int x = 0, y = 0, p = 0;
  while (n--) {
    if (!col[x][y]) {
      p = (p + 1) % 4;
      col[x][y] = 1;
    } else {
      p = (p + 3) % 4;
      col[x][y] = 0;
    }
    x = (x + d[p][0] + h) % h, y = (y + d[p][1] + w) % w;
  }

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (col[i][j]) std::cout << "#";
      else std::cout << ".";
    }
    std::cout << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
