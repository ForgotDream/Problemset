#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int xa, xb, xc;
  int ya, yb, yc;
  std::cin >> xa >> ya >> xb >> yb >> xc >> yc;

  int dx1 = xa - xb, dx2 = xa - xc;
  int dy1 = ya - yb, dy2 = ya - yc;

  int ans = 1;
  if (dx1 >= 0 && dx2 >= 0) {
    ans += std::min(dx1, dx2);
  } else if (dx1 < 0 && dx2 < 0) {
    ans += std::min(-dx1, -dx2);
  }
  if (dy1 >= 0 && dy2 >= 0) {
    ans += std::min(dy1, dy2);
  } else if (dy1 < 0 && dy2 < 0) {
    ans += std::min(-dy1, -dy2);
  }

  std::cout << ans << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}