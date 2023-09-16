#include <iomanip>
#include <iostream>

using i64 = long long;

int a[4][4], cnt;
void calc() {
  for (int i = 1; i <= 3; i++) {
    if (a[i][1] == a[i][2] && a[i][2] != a[i][3]) cnt++;
    if (a[1][i] == a[2][i] && a[2][i] != a[3][i]) cnt++;
  }
  if (a[1][1] == a[2][2] && a[2][2] != a[3][3]) cnt++;
  if (a[1][3] == a[2][2] && a[2][2] != a[3][1]) cnt++;
}
void solve() {
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) std::cin >> a[i][j];
  }
  calc();
  std::cout << std::fixed << std::setprecision(12) << 
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}