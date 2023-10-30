#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 10;
int n;
std::string r, c;
int cntr[N][3], cntc[N][3];
char a[N][N];
bool check() {
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 3; j++) {
      if (!cntr[i][j] || cntr[i][j] > 1) return false;
      if (!cntc[i][j] || cntc[i][j] > 1) return false;
    }
  }
  return true;
}
bool topmost(int x, int y) {
  for (int i = 1; i < x; i++) {
    if (a[i][y] != '.') return false;
  }
  return true;
}
bool leftmost(int x, int y) {
  for (int i = 1; i < y; i++) {
    if (a[x][i] != '.') return false;
  }
  return true;
}
void dfs(int x, int y) {
  if (x == n + 1) {
    if (check()) {
      std::cout << "Yes\n";
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) std::cout << a[i][j];
        std::cout << "\n";
      }
      exit(0);
    }
    return;
  }
  if (y == n + 1) return dfs(x + 1, 1);
  if (topmost(x, y)) {
    int d = c[y] - 'A';
    if (!cntr[x][d] && !cntc[y][d]) {
      a[x][y] = c[y], cntr[x][d]++, cntc[y][d]++, dfs(x, y + 1);
      cntr[x][d]--, cntc[y][d]--;
    }
    a[x][y] = '.', dfs(x, y + 1);
  } else if (leftmost(x, y)) {
    int d = r[x] - 'A';
    if (!cntr[x][d] && !cntc[y][d]) {
      a[x][y] = r[x], cntr[x][d]++, cntc[y][d]++, dfs(x, y + 1);
      cntr[x][d]--, cntc[y][d]--;
    }
    a[x][y] = '.', dfs(x, y + 1);
  } else {
    for (int i = 0; i < 3; i++) {
      if (cntr[x][i] || cntc[y][i]) continue;
      a[x][y] = i + 'A', cntr[x][i]++, cntc[y][i]++, dfs(x, y + 1);
      cntr[x][i]--, cntc[y][i]--;
    }
    a[x][y] = '.', dfs(x, y + 1);
  }
}
void solve() {
  std::cin >> n >> r >> c;
  r = " " + r, c = " " + c;
  if (r[1] != c[1]) {
    std::cout << "No\n";
    return;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) a[i][j] = '.';
  }
  dfs(1, 1);
  std::cout << "No\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
