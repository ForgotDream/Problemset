/**
 * @file    CF437E The Child and Polygon.cpp
 * @author  ForgotDream
 * @brief   Interval DP
 * @date    2023-11-03
 */
#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 250, mod = 1e9 + 7;
int n;
struct Vector {
  i64 x, y;
  friend i64 cross(const Vector &lhs, const Vector &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }
};
struct Point {
  i64 x, y;
  explicit operator Vector() { return {x, y}; }
  // operator Vector() { return {x, y}; }
  friend Vector operator-(const Point &lhs, const Point &rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
  }
} p[N];
i64 f[N][N];
void solve() {
  std::cin >> n;
  i64 sum = 0;
  for (int i = 1; i <= n; i++) {
    std::cin >> p[i].x >> p[i].y;
    if (i != 1) sum += cross(Vector(p[i - 1]), Vector(p[i]));
  }
  sum += cross(Vector(p[n]), Vector(p[1]));
  if (sum > 0) std::reverse(p + 1, p + n + 1);
  for (int i = 1; i < n; i++) f[i][i + 1] = 1;
  for (int len = 3; len <= n; len++) {
    for (int l = 1; l <= n - len + 1; l++) {
      int r = l + len - 1;
      for (int k = l + 1; k < r; k++) {
        if (cross(p[r] - p[l], p[k] - p[l]) > 0) {
          f[l][r] = (f[l][r] + f[l][k] * f[k][r] % mod) % mod;
        }
      }
    }
  }
  std::cout << f[1][n] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
